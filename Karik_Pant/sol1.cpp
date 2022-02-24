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
    person_val[name] = idx;
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
  bool completed;
  void read() {
    completed = false;
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
    vector<pair<int,int>> _set_busy;
    bool found = false;
    for (auto R: req) {
      found = false;
      // cout << "checking for " << skills[R.first].name << " --- " << R.second << '\n';
      for (int i = R.second; i < 105; ++i) {
        for (const string& name: skills[R.first].persons[i]) {
          int pp = person_val[name];
          // cout << "for " << name << " -- " << busy[pp] << '\n';
          if (busy[pp] > day)
            continue;
          found = true;
          _set_busy.push_back({ pp, busy[pp] });
          busy[pp] = day + meta[0];
          people.push_back(name);
          break;
        }
        if (found) break;
      }
      if (!found) break;
    }
    if (!found) {
      for (auto val: _set_busy) 
        busy[val.first] = val.second;
      return vector<string>();
    }
    completed = true;
    return people;
  }
};

int main () {
  int C, P;
  cin >> C >> P;

  busy.resize(C, 0);
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
      return A.meta[1] < B.meta[1];
    });

  vector<string> ans_pro;
  vector<vector<string>> ans_con;
  set<int> day; day.insert(0);
  int mx = -1;
  while (!day.empty()) {
    mx = max(mx, *day.begin());
    for (Project& project: projects) {
      if (project.completed) continue;
      vector<string> names = project.find_people(*day.begin());
      if ((int)names.size() != 0) {
        ans_pro.push_back(project.name);
        ans_con.push_back(names);
        if (*day.begin() + project.meta[0] > mx)
          day.insert(*day.begin() + project.meta[0]);
      }
    }
    day.erase(*day.begin());
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
