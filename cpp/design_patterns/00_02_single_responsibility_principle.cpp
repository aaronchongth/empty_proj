// Avoid God objects
struct Journal
{
  string title;
  vector<string> entries;

  explicit Journal(const string& title) : title{title} {}
};

// then we implement something for adding stuff
void Journal::add(const string& entry)
{
  static int count = 1;
  entries.push_back(boost::lexical_cast<string>(count++) + ": " + entry);
}

// then we can call
Journal j("Dear Diary");
j.add("I cried today");
j.add("I ate a bug");

// but what happens when we want to save stuff?
void Journal::save(const string& filename)
{
  ofstream ofs(filename);
  for (auto& s : entries)
    ofs << s << endl;
}

// journals keep entries, not write them to disk, a better approach would be
struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto& s : j.entries)
      ofs << s << endl;
  }
};

// it will be scalable too, for when we have something other than journals that
// require persistence.
