#include <bits/stdc++.h>
using namespace std;

unordered_map<string,int> person_val;
unordered_map<string,int> skill_val;

struct Skill {
  string name;
  vector<set<string>> persons;
  Skill(string _name) {
    name = _name;
    persons.resize(105);
  }
  void add_person(string person, int level) {
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
      skills[skill_val[skill]].add_person(name, lvl);
    }
  }
};

vector<Person> persons;
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
      cout << A.first << ' ' << A.second << '\n';
      bool found = false;
      for (int i = A.second; i < 105; ++i) {
        for (const string& name: skills[A.first].persons[i]) {
          if (persons[person_val[name]].busy) 
            continue;
          found = true;
          people.push_back(name);
          persons[person_val[name]].busy = true;
          cout << "Found one person for " << A.first << " skill = " << people.back() << '\n';
        }
        if (found) break;
      }
      if (!found) {
        return vector<string>();
      }
    }
    return people;
  }
};

int main () {
  int C, P;
  cin >> C >> P;

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
