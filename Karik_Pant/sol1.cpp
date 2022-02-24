#include <bits/stdc++.h>
using namespace std;

unordered_map<string,int> person_val;
unordered_map<string,int> skill_val;

struct Skill {
  string name;
  unordered_map<int,set<int>> persons;
  Skill(string _name) {
    name = _name;
  }
  void add_person(int person, int level) {
    persons[level].insert(person);
  }
};

vector<Skill> skills;
struct Person {
  string name;
  bool busy;
  void read(int idx) {
    busy = false;
    cin >> name;
    int cc; cin >> cc;
    while (cc--) {
      string skill; cin >> skill;
      int lvl; cin >> lvl;
      if (skill_val.find(skill) == skill_val.end()) {
        skill_val.insert({ skill, int(skills.size()) });
        skills.push_back(Skill(skill));
      }
      skills[skill_val[skill]].add_person(idx, lvl);
    }
  }
};

struct Project {
  string name;
  vector<int> meta;
  vector<pair<int,int>> req;
  void read() {
    meta.resize(4);
    cin >> name;
    for (int i = 0; i < 4; ++i) {
      cin >> meta[i];
    }
    req.resize(meta.back());
    for (int i = 0; i < meta.back(); ++i) {
      string skill; int lvl;
      cin >> skill >> lvl;
      req[i] = { skill_val[skill], lvl };
    }
  }
};

int main () {
  int C, P;
  cin >> C >> P;

  vector<Person> persons;
  for (int i = 0; i < C; ++i) {
    Person person; person.read(i);
    persons.push_back(person);
  }

  vector<Project> projects;
  for (int i = 0; i < P; ++i) {
    Project project; project.read();
    projects.push_back(project);
  }

  cout << "Skills = " << skills.size() << '\n';

  return 0;
}
