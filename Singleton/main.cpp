#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Number
{

  public:
    virtual ~Number() {
        cout << "Number dtor\n";
    }

    // 2. Define a public static accessor func
    static Number * instance();
    static void deinit();

    static void setType( string a_type ){
      s_type = a_type;
      delete s_inst;
      s_inst = nullptr;
    }

    virtual void setValue( int a_value ) { m_value = a_value; }
    virtual int value() { return m_value; }

  protected:

    int m_value;
    // 4. Define all ctors to be protected
    Number() {
        cout << "Number ctor: ";
    }


  // 1. Define a private static attribute
  private:
    static string s_type;
    static Number * s_inst;
};

string Number::s_type = "decimal";
Number *Number::s_inst = nullptr;

class Octal: public Number
{

  public:

    virtual ~Octal() {
        cout << "Octal dtor\n";
    }

    // 6. Inheritance can be supported
    friend class Number;

    void setValue(int a_value)
    {
      char buf[10];
      sprintf(buf, "%o", a_value);
      sscanf(buf, "%d", &m_value);
    }
  protected:
    Octal(){ cout << "Octal ctor: ";}
};

Number * Number::instance()
{
  if ( !s_inst ) {
    if (s_type == "octal")
      s_inst = new Octal();
    else
      s_inst = new Number();
  }
  return s_inst;
}

void Number::deinit()
{
    if ( s_inst ) {
        cout << "Number deinit\n";
        delete s_inst;
        s_inst = nullptr;
    }
}


int main() {

    // Number  myInstance; - error: cannot access protected constructor
    // 5. Clients may only use the accessor function to manipulate the Singleton
    Number::instance()->setValue(42);
    cout << "value is " << Number::instance()->value() << endl;
    Number::setType("octal");
    Number::instance()->setValue(64);
    cout << "octal value is " << Number::instance()->value() << endl;

    Number::deinit();

    Number::setType("decimal");
    Number::instance()->setValue(54);
    cout << "value is " << Number::instance()->value() << endl;

    Number::deinit();

    return 0;
}
