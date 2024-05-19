/*%!@$!@$%&&$#@%@^#%&$**($%&%#$%@#%^#@^&#@$%#!@^@#^&@#^
░██████╗░█████╗░███╗░░░███╗██╗░░░██╗██████╗░░█████╗░██╗
██╔════╝██╔══██╗████╗░████║██║░░░██║██╔══██╗██╔══██╗██║
╚█████╗░███████║██╔████╔██║██║░░░██║██████╔╝███████║██║
░╚═══██╗██╔══██║██║╚██╔╝██║██║░░░██║██╔══██╗██╔══██║██║
██████╔╝██║░░██║██║░╚═╝░██║╚██████╔╝██║░░██║██║░░██║██║
╚═════╝░╚═╝░░╚═╝╚═╝░░░░░╚═╝░╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚═╝
^@#^@&@#%@*^%*&$%^#$^$***%^#$@%$@#$!@$!@#$%@#^@&@#%@#*/
//#include <bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <stack>
#include <numeric>
#include <unordered_map>
#include <bitset>
#include <limits>
#include <queue>
#include <sstream>
#include <thread>

using namespace std;

#define send {ios_base::sync_with_stdio(false);}
#define help {cin.tie(NULL);}
#define pls  {cout.tie(0);}
#define endl		"\n"
#define ll			long long int
#define ull			unsigned long long	
#define pll			pair<ll,ll> 
#define not_less_than(v, n) lower_bound(v.begin(), v.end(), n)                   // n >=
#define not_more_than(v, n) lower_bound(v.rbegin(), v.rend(), n, greater<ll>()) // n <=
#define more_than(v, n) upper_bound(v.begin(), v.end(), n)                       // n <
#define less_than(v, n) upper_bound(v.rbegin(), v.rend(), n, greater<ll>())     // n >
#define getunique(v) {sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());}
#define sps(pvec) sort(pvec.begin(),pvec.end(),[](const auto &a,const auto &b){return a.second<b.second;});
#define frq(mp) for(auto &element:mp)cout<<element.first<<" "<<element.second<<endl;
#define sw(x, y) \
    if (x < y)   \
        swap(x, y);
#define REP(o,l,r) for(long long o=(l);o<(r);o++)
#define PER(o,l,r) for(long long o=(r)-1;o>=(l);o--
#define debug(x)	cout<<'['<<#x<<" is "<<x<<"]"<<endl;
#define all(d)		d.begin(),d.end()
#define rall(d)		d.rbegin(), d.rend()
#define fe(d)	for(auto &oI : d) {cout << oI << " ";} cout << endl;

ll mx = 10000;

vector<vector<ll>> keyCombos;

vector<ll> generateRandomKey() {
	vector<ll> key;
	for (int o = 0; o < 16; o++)
		key.push_back(static_cast<ll>(rand() % 10));
	return key;
}


void initialize_RC4(vector<ll>& key, vector<ll>& S) {
	for (int o = 0; o < 256; o++)
		S[o] = o;
	ll j(0);
	for (int o = 0; o < 256; o++)
	{
		j = (j + S[o] + key[o % key.size()]) % 256;
		swap(S[o], S[j]);
	}
}

vector<ll> GenerateRC4Keystream(vector<ll>& S, ll length) {
	vector<ll> keystream;
	int o(0), j(0);
	while (keystream.size() < length) {
		o = (o + 1) % 256;
		j = (j + S[o]) % 256;
		swap(S[o], S[j]);
		keystream.push_back(S[(S[o] + S[j]) % 256]);
	}
	return keystream;
}

vector<ll> getCurrentKey(vector<ll>& key, ll idx) {
	vector<ll> newCombo = keyCombos[idx], result;
	for (int o = 0; o < key.size(); o++)
	{
		if (o <= 3)
			result.push_back(newCombo[o]);
		else {
			result.push_back(key[o]);
		}
	}
	return result;
}

double experiment(vector<ll>& key) {
	int count = 0;
	for (int trial = 0; trial < 10000; trial++) {
		vector<ll> S(256);
		vector<ll> currentKey = getCurrentKey(key, trial);
		initialize_RC4(currentKey, S);
		vector<ll> keyS = GenerateRC4Keystream(S, 256);
		if (keyS[1] == 0) {
			count++;
		}
	}
	return static_cast<double>(count) / mx;
}


double calculteHammingDistance(vector<ll>& a, vector<ll>& b) {
	ll s(0);
	for (int o = 0; o < a.size(); o++)
	{
		if (a[o] != b[o])
			s++;
	}
	return static_cast<double> (s) / (a.size());
}

double doJob(vector<ll>& secret_key) {
	vector<ll> secret_keyv2(all(secret_key));
	secret_keyv2[0] = (secret_keyv2[0] + 1) % 9;
	vector<ll> S(256);
	initialize_RC4(secret_key, S);
	vector<ll> secret_key_output = GenerateRC4Keystream(S, 256);
	vector<ll> S2(256);
	initialize_RC4(secret_keyv2, S2);
	vector<ll> secret_key_outputv2 = GenerateRC4Keystream(S2, 256);
	return calculteHammingDistance(secret_key_output, secret_key_outputv2);
}

double proveZerosPairWeakness(vector<ll>& key, ll x) {
	vector<ll> S(256);
	initialize_RC4(key, S);

	ll zerosCount = 0;
	ll i = 0, j = 0;

	for (ll n = 0; n < x; n++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(S[i], S[j]);
		ll k = S[(S[i] + S[j]) % 256];
		if (n > 0) {
			if (S[i] == 0 && k == 0) {
				zerosCount++;
			}
		}
	}

	double probability = static_cast<double>(zerosCount) / (x - 1);
	return probability;
}

void generateKeyCombo() {
	for (int d1 = 0; d1 <= 9; d1++) {
		for (int d2 = 0; d2 <= 9; d2++) {
			for (int d3 = 0; d3 <= 9; d3++) {
				for (int d4 = 0; d4 <= 9; d4++) {
					keyCombos.push_back({ d1, d2, d3, d4 });
				}
			}
		}
	}
}

void Clear() {
	system("clear");
}

void DelaySeconds(ll sec) {
	this_thread::sleep_for(chrono::seconds(sec));
}

void solution() {
	vector<ll> key = { 1,2,3,4,5,6,7,8,9,10 };
	cout << experiment(key) << endl;
}

int32_t main() {
	// send help pls
	Clear();
	generateKeyCombo();
	ll option(0);
	vector<ll> key;
	while (true)
	{
		cout << "RC4 Key and Weakness Testing\n";
		cout << "1. Enter a 128-bit key manually\n";
		cout << "2. Generate a random 128-bit key\n";
		cout << "3. Perform tests to prove weaknesses in RC4\n";
		cout << "4. Exit\n";
		cout << "Select an option: ";
		cin >> option;

		switch (option) {
			case 1: {
				Clear();
				cout << "Please enter your key." << endl;
				string str;
				cin >> str;
				if (str.size() > 16)
				{
					cout << "please provide a valid length" << endl;
					return 0;
				}
				for (int o = 0; o < str.size(); o++)
					key.push_back(str[o] - '0');
				cout << "Key has been set!" << endl;
				break;
			}
			case 2: {
				Clear();
				key = generateRandomKey();
				cout << "key has been generated" << endl;
				for (int o = 0; o < 16; o++)
					cout << key[o] << ' ';
				cout << endl;
				break;
			}
			case 3: {
				Clear();
				if(!key.size()) {
					cout << "Key is required." << endl;
					break;
				}
				cout << "Select a test to perform:\n";
				cout << "  a. First Weakness\n";
				cout << "  b. (0,0) Pair Weakness\n";
				cout << "  c. Related Key Attacks\n";
				cout << "Enter choice (a, b, c, all): ";
				string testOption; cin >> testOption;
				Clear();
				if (testOption == "a") {
					cout << "First test:" << endl;
					cout << experiment(key) << endl;
				}
				else if (testOption == "b") {
					ll mxTries = 1e6;
					cout << "Empirical Probability of (0,0) pair: " << proveZerosPairWeakness(key, mxTries) << endl;
					cout << "Theoretical Probability of (0,0) pair: " << 2.0 / (256.0 * 256.0) + 1.0 / (256.0 * 256.0 * 256.0) << endl;
				}
				else if (testOption == "c") {
					cout << doJob(key) << endl;
				}
				else if(testOption == "all") {
					cout << "First test: " << endl;
					cout << experiment(key) << endl;
					cout << "Second test: " << endl;
					ll mxTries = 1e6;
					cout << "Empirical Probability of (0,0) pair: " << proveZerosPairWeakness(key, mxTries) << endl;
					cout << "Theoretical Probability of (0,0) pair: " << 2.0 / (256.0 * 256.0) + 1.0 / (256.0 * 256.0 * 256.0) << endl;
					cout << "Third test: " << endl;
					cout << doJob(key) << endl;

				} else {
					cout << "Invalid test option my dude.\n";
				}
				DelaySeconds(3);
				break;
			}
			case 4: {
				Clear();
				cout << "Exiting program.\n";
				return 0;
			}
			default: {
				Clear();
				cout << "Invalid option. Please try again.\n";
				break;
			}
		}
		DelaySeconds(3);
		Clear();
	}
	return 0;
}
