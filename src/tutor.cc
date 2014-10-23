#include "tutor.hh"


/* ********************************************************************************************* *
 * Trainer interface
 * ********************************************************************************************* */
Tutor::Tutor(QObject *parent)
  : QObject(parent)
{
  // pass...
}

Tutor::~Tutor() {
  // pass...
}


/* ********************************************************************************************* *
 * KochTrainer
 * ********************************************************************************************* */
inline QVector<QChar> _initKochLessons() {
  QVector<QChar> chars;
  chars << 'k' << 'm' << 'r' << 's' << 'u' << 'a' << 'p' << 't' << 'l' << 'o' << 'w'
        << 'i' << '.' << 'n' << 'j' << 'e' << '=' << 'f' << '0' << 'y' << 'v' << ','
        << 'g' << '5' << '/' << 'q' << '9' << 'z' << 'h' << '3' << '8' << 'b' << '?'
        << '4' << '2' << '7' << 'c' << '1' << 'd' << '6' << 'x' << '=';
  return chars;
}
// The vector of all chars ordered by lesson
QVector<QChar> KochTutor::_lessons = _initKochLessons();


KochTutor::KochTutor(int lesson, QObject *parent)
  : Tutor(parent), _lesson(lesson), _text()
{
  // Init random number generator
  srand(time(0));
}

KochTutor::~KochTutor() {
  // pass...
}

QChar
KochTutor::next() {
  if (0 == _text.size()) { reset(); }
  QChar ch = _text.first(); _text.pop_front();
  return ch;
}

bool
KochTutor::atEnd() {
  return 0 == _text.size();
}

int
KochTutor::lesson() const {
  return _lesson;
}
void
KochTutor::setLesson(int lesson) {
  _lesson = std::max(2, std::min(lesson, _lessons.size()));
}

void
KochTutor::reset()
{
  // Empty current session
  _text.clear();
  // Insert "vvv\n"
  _text.push_back('v'); _text.push_back('v'); _text.push_back('v'); _text.push_back('\n');

  // For 5 lines
  for (int l=0; l<5; l++) {
    // and 5 groups
    for (int g=0; g<5; g++) {
      // of 5 chars
      for (int c=0; c<5; c++) {
        // Sample char from lesson
        size_t idx = _lesson*double(rand())/RAND_MAX;
        _text.push_back(_lessons[idx]);
      }
      _text.push_back(' ');
    }
    _text.push_back('=');
    _text.push_back('\n');
  }
}