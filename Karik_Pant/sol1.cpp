#include <bits/stdc++.h>
using namespace std;

unordered_map<string,int> person_val;
unordered_map<string,int> skill_val;

struct Skill {
  string name;
  map<int,set<string>> persons;
  Skill(string _name) {
    name = _name;
  }
  void add_person(string person, int level) {
    persons[level].insert(person);
  }
};

vector<Skill> skills;
struct Person {
  string name;
  int busy;
  void read(int idx) {
    cin >> name;
    int cc; cin >> cc;
    while (cc--) {
      string skill; cin >> skill;
      int lvl; cin >> lvl;
      if (skill_val.find(skill) == skill_val.end()) {
        skill_val.insert({ skill, int(skills.size()) });
        skills.push_back(Skill(skill));
      }
      skills[skill_val[skill]].add_person(name, lvl);
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
  vector<string> find_people() {
    vector<string> people;
    for (auto A: req) {
      auto it = *skills[A.first].persons.rbegin();
      if (it.first >= A.second) {
        people.push_back(*it.second.begin());
      } else {
        people.resize(0);
        return people;
      }
    }
    return people;
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

  // sorting projects on the basis of their deadlines
  sort(projects.begin(), projects.end(), [&](const Project& A, const Project& B) {
      return A.meta[1] > B.meta[1];
    });

  for (Project& project: projects) {
    vector<string> names = project.find_people();
    if ((int)names.size() != 0) {
      cout << "1\n";
      cout << project.name << '\n';
      for (const string& name: names) 
        cout << name << ' ';
      cout << '\n';
      break;
    }
  }

  return 0;
}
