struct MyFavoritePrinter /* : IMachine */
{
  void print(vector<Document*> docs) override;
  void fax(vector<Document*> docs) override;
  void scan(vector<Document*> docs) override;
};

// Now we decide to define an interface that needs to be implemented by
// everyone who plans to make a multifunction printer.
struct IMachine
{
  virtual void print(vector<Document*> docs) override = 0;
  virtual void fax(vector<Document*> docs) override = 0;
  virtual void scan(vector<Document*> docs) override = 0;
};

// but we are forcing everyone to use these functions, they can be no-op, but
// there is a better way
struct IPrinter
{
  virtual void print(vector<Document*> docs) = 0;
}

struct IScanner
{
  virtual void scan(vector<Document*> docs) = 0;
};

// normal printers and scanners
struct Printer : IPrinter
{
  void print(vector<Document*> docs) override;
};

struct Scanner : IScanner
{
  void scan(vector<Document*> docs) override;
};

// if we want a machine that can print and scan
struct IMachine : IPrinter, IScanner /*IFax and so on */
{
};

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner)
  : printer{printer},
    scanner{scanner}
  {}

  void print(vector<Document*> docs) override
  {
    printer.print(docs);
  }

  void scan(vector<Document*> docs) override
  {
    scanner.scan(docs);
  }
};
