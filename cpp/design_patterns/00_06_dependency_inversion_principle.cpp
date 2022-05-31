// for example Reporting depends on an ILogger
class Reporting
{
  ILogger& logger;
public:
  Reporting(const ILogger& logger)
  : logger{logger}
  {}

  void prepare_report()
  {
    logger.log_info("Preparing the report");
    // ...
  }
};

// What if Reporting is dependent upon five different interfaces?
// What if ConsoleLogger has deps of its own?
// You can write a lot of code, but there is a better way

// dependency injection
struct Engine
{
  float volume = 5;
  int horse_power = 400;

  friend ostream& operator<<(ostream& os, const Engine& obj)
  {
    return os
      << "volume: " << obj.volume
      << " horse_power: " << obj.horse_power;
  }
};

// now we decide whther to extract an IEngine interface and feed it to the car
// we will also want logging
struct ILogger
{
  virtual ~ILogger() {}
  virtual void Log(const string& s) = 0;
};

// as well as its concrete implementation
struct ConsoleLogger : ILogger
{
  ConsoleLogger() {}

  void Log(const string& s) override
  {
    cout << "LOG: " << s.c_str() << endl;
  }
};

// now the car
struct Car
{
  unique_ptr<Engine> engine;
  shared_ptr<ILogger> logger;

  Car(unique_ptr<Engine> engine, const shared_ptr<ILogger>& logger)
  : engine{move(engine)},
    logger{logger}
  {
    logger->Log("making a car");
  }

  friend ostream& operator<<(ostream& os, const Car& obj)
  {
    return os << "car with engine: " << *obj.engine;
  }
};

// this means, any time someone asks for an ILogger give them a ConsoleLogger
auto injector = di::make_injector(
  di::bind<ILogger>().to<ConsoleLogger>());

auto car = injector.create<shared_ptr<Car>>();

// I think we can use something else in STL instead of boost.
// probably dynamic casting the pointer into the interface.
