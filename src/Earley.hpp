

class Grammatic {
 public:
 private:
};

class EarleyParser {
 public:
  void Initialise();
  void Parse();

 private:
  void Scan();
  void Predict();
  void Complete();
};