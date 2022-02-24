//you cannot compare two numbers after taking their mod i.e. a<b != a%mod < b%mod
//clear adj and visited vector declared globally after each test case
//check for long long overflow
//while adding and subs check if mod becomes -ve
//while using an integer directly in a builtin function add ll
//Mod wale question mein last mein if dalo ie. Ans<0 then ans+=mod;
//Dont keep array name as size or any other key word
/*
    Don't forget
    1. If you are looking at editorial, remember that you are accepting defeat.
    2. [If stuck] Don't stick to one approach and attack with different approaches.
    Write everything down, analyze the G-spot and attack throught it.
    3. Don't look at standings during the contest.
    4. Don't try to code fast and code concetrately instead or bugs will eat you in the sleep.
    5. When you are writing return, make sure that there are no input/global operations after that
*/
#include<bits/stdc++.h>

using namespace std;



#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define nline "\n"
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>

// using namespace std;
// using namespace __gnu_pbds;
// typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key

#ifdef TUSHAR
	#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
	#define debug(x)
#endif

void _print ( ll t ) {cerr << t;}
void _print ( int t ) {cerr << t;}
void _print ( string t ) {cerr << t;}
void _print ( char t ) {cerr << t;}
void _print ( lld t ) {cerr << t;}
void _print ( double t ) {cerr << t;}
void _print ( ull t ) {cerr << t;}

template <class T, class V> void _print ( pair <T, V> p );
template <class T> void _print ( vector <T> v );
template <class T> void _print ( set <T> v );
template <class T, class V> void _print ( map <T, V> v );
template <class T> void _print ( multiset <T> v );
template <class T, class V> void _print ( pair <T, V> p ) {cerr << "{"; _print ( p.ff ); cerr << ","; _print ( p.ss ); cerr << "}";}
template <class T> void _print ( vector <T> v ) {cerr << "[ "; for ( T i : v ) {_print ( i ); cerr << " ";} cerr << "]";}
template <class T> void _print ( set <T> v ) {cerr << "[ "; for ( T i : v ) {_print ( i ); cerr << " ";} cerr << "]";}
template <class T> void _print ( multiset <T> v ) {cerr << "[ "; for ( T i : v ) {_print ( i ); cerr << " ";} cerr << "]";}
template <class T, class V> void _print ( map <T, V> v ) {cerr << "[ "; for ( auto i : v ) {_print ( i ); cerr << " ";} cerr << "]";}
bool isPrinting = false;
string debugging = "local";

void getOutputs();
void local();
class Skill {
	public:
		string skill;
		int key;
		int level;
		Skill ( string sk, int k, int lev ) : skill ( sk ), key ( k ), level ( lev ) {}
		operator std::string() const {
			return "\nskill: " + skill + " level: " + to_string ( level );
		}
		
};
class Contributor {
	public:
		string name;
		int skills;
		vector<Skill> skill;
		operator std::string() const {
			return "\nname: " + name;
		}
};

class Project {
	public:
		string name;
		vector<Skill> skills;
		int roles;
		int duration;
		int bestScore;
		int bestBefore;
		operator std::string() const {
			return "\nname: " + name + " duration: " + to_string ( duration ) + " bestScore: " + to_string ( bestScore ) + " bestBefore: " + to_string ( bestBefore );
		}
		
};

int backtrack ( vector<Project>& p, vector<Contributor>& c, vector<bool>& done, int doneCount, int presentDay, vector<bool>& available ) {
	if ( doneCount == done.size() ) {
		return 0;
	}
	for ( int i = 0; i < p.size(); i++ ) {
		if ( done[i] == false ) {
			for ( int j = 0; j < contributors.size(); j++ ) {
				if ( available[j] == true ) {
					for ( int k = 0; k < contributors[j].skill; k++ ) {
					}
				}
			}
		}
	}
}

void main1() {
	int P, C;
	cin >> C >> P;
	vector<Contributor> contributors ( C );
	vector<Project> projects ( P );
	map<string, int> skillsMap, contributorsMap, projectsMap;
	map<int, string> skillsMapRev, contributorsMapRev, projectsMapRev;
	for ( int i = 0; i < C; i++ ) {
		// string name;
		cin >> contributors[i].name >> contributors[i].skills;
		if ( contributorsMap.count ( contributors[i].name ) == 0 ) {
			contributorsMap[contributors[i].name] = contributorsMap.size();
			contributorsMapRev[contributorsMap[contributors[i].name]] = contributors[i].name;
		}
		for ( int j = 0; j < contributors[i].skills; j++ ) {
			string skill;
			int level;
			cin >> skill >> level;
			if ( skillsMap.count ( skill ) == 0 ) {
				skillsMap[skill] = skillsMap.size();
				skillsMapRev[skillsMap[skill]] = skill;
			}
			contributors[i].skill.pb ( Skill ( skill, skillsMap[skill], level ) );
		}
	}
	for ( int i = 0; i < P; i++ ) {
		cin >> projects[i].name;
		cin >> projects[i].duration >> projects[i].bestScore >> projects[i].bestBefore >> projects[i].roles;
		if ( projectsMap.count ( projects[i].name ) == 0 ) {
			projectsMap[projects[i].name] = projectsMap.size();
			projectsMapRev[projectsMap[projects[i].name]] = projects[i].name;
		}
		for ( int j = 0; j < projects[i].roles; j++ ) {
			string skill;
			int level;
			cin >> skill >> level;
			if ( skillsMap.count ( skill ) == 0 ) {
				skillsMap[skill] = skillsMap.size();
				skillsMapRev[skillsMap[skill]] = skill;
			}
			projects[i].skills.pb ( Skill ( skill, skillsMap[skill], level ) );
		}
	}
	sort ( all ( projects ), [] ( const Project & p1, const Project & p2 ) {
		return p1.bestBefore < p2.bestBefore;
	} );
	sort ( all ( contributors ), [] ( const Contributor & c1, const Contributor & c2 ) {
		return c1.skills > c2.skills;
	} );
}

int main() {
	local();
	// getOutputs();
	// fastio();
	return 0;
}

void local() {
	#ifdef TUSHAR
	freopen ( "in.txt", "r", stdin );
	freopen ( "out.txt", "w", stdout );
	freopen ( "Error.txt", "w", stderr );
	#endif
	debug ( debugging )
	main1();
}
void getOutputs() {
	if ( !isPrinting ) {
		isPrinting = true;
	} else {
		return;
	}
	int TC = 8;
	const char* str[] = {"in_a.txt", "in_b.txt", "in_c.txt", "in_d.txt", "in_e.txt", "in_f.txt", "in_g.txt", "in_h.txt"};
	const char* str1[] = {"out_a.txt", "out_b.txt", "out_c.txt", "out_d.txt", "out_e.txt", "out_f.txt", "out_g.txt", "out_h.txt"};
	debugging = "a";
	for ( int i = 0; i < TC; i++ ) {
		debugging = str[i];
		freopen ( str[i], "r", stdin );
		freopen ( str1[i], "w", stdout );
		freopen ( "Error.txt", "w", stderr );
		debug ( debugging )
		main1();
	}
}