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

vector<Person> persons;
vector<int> busy;
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
  vector<string> find_people(int day) {
    vector<string> people;
    for (auto R: req) {
      vector<int> set_busy;
      bool found = false;
      for (int lvl = R.second; lvl < 105; ++lvl) {
        for (const string& name: skills[R.first].persons[lvl]) {
          if (busy[person_val[name]] > day)
            continue;
          found = true;
          busy[person_val[name]] += meta[1];
          people.push_back(name);
          break;
        }
      }
      if (!found) {
        for (const int& val: set_busy) {
          busy[val] -= meta[1];
        }
        return vector<string>();
      }
    }
    return people;
  }
};

int main () {
  int C, P;
  cin >> C >> P;

  busy.resize(P, 0);
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

  vector<string> ans_pro;
  vector<vector<string>> ans_con;
  for (Project& project: projects) {
    cout << "Checking for project " << project.name << '\n';
    vector<string> names = project.find_people(0);
    if ((int)names.size() != 0) {
      ans_pro.push_back(project.name);
      ans_con.push_back(names);
    }
  }

  cout << ans_pro.size() << '\n';
  for (int i = 0; i < (int)ans_pro.size(); ++i) {
    cout << ans_pro[i] << '\n';
    for (const string& p_name: ans_con[i])
      cout << p_name << ' ';
    cout << '\n';
  }

  return 0;
}
