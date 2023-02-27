#include "map.h"
#include <assert.h>

void insertABC(Map& m) {
    m.insert("a", "A");
    m.insert("b", "B");
    m.insert("c", "C");
}

void insertXYZ(Map& m) {
    m.insert("a", "X");
    m.insert("b", "Y");
    m.insert("c", "Z");
}

void insertPDQ(Map& m) {
    m.insert("c", "P");
    m.insert("a", "D");
    m.insert("b", "Q");
}

void insertAlternatingKeys(Map& m) {
    for (int i = 0; i < 12; i++) {
        string key0 = string(1, 65+13+i);
        string key1 = string(1, 65+12-i);
        m.insert(key0, key0);
        m.insert(key1, key1);
    }
}

void insertBalancedKeys(Map& m) {
    for (int i = 0; i < 6; i++) {
        string key0 = string(1, 65+13+6+i);
        string key1 = string(1, 65+12-6-i);
        string key2 = string(1, 65+13+6-1);
        string key3 = string(1, 65+12-6+i);
        m.insert(key0, key0);
        m.insert(key1, key1);
        m.insert(key2, key2);
        m.insert(key3, key3);
    }
}

void insertRandomKeys(Map& m, int count, int max_key) {
    for (int i = 0; i < count; i++) {
        int key = rand() % max_key;
        m.insert(to_string(key), to_string(key));
    }
}

int main() {
    Map a;
    insertAlternatingKeys(a);
    assert(a.size() == 24);
    Map b;
    insertBalancedKeys(b);
    assert(a.size() == 24);
    Map c;
    insertABC(c);
    cout << c << endl;
    Map d = c;
    cout << d << endl;
    Map e;
    e = d;
    cout << e << endl;

    Map f;
    insertRandomKeys(f, 100000, 100);
    cout << "size is likely to be 100, size = " << f.size() << endl;

    Map empty;
    Map empty1 = empty;
    Map empty2;
    empty2 = empty;

    assert(empty.begin() == empty.end());

    insertRandomKeys(empty2, 100000, 10);
    cout << "size is likely to be 10, size = " << empty2.size() << endl;
    cout << empty2;

    Map::Iterator it = empty2.find("8");
    cout << (*it).data << " should be 8" << endl;
    assert(empty2.find("8") == it);

    it = empty2.find("9");
    cout << it->data << " should be 9" << endl;
    assert(empty2.find("8") != it);

    assert(empty2.find("neither here") == empty2.end());
    assert(empty2.find("neither here") == empty2.find("nor there"));

    Map begin;
    insertPDQ(begin);
    assert(begin.begin()->data == "P");

    Map erase;
    erase.insert("8", "8");
    erase.insert("3", "3");
    erase.insert("5", "5");
    erase.insert("1", "1");
    erase.insert("2", "2");

    cout << erase << endl;

    Map s;
    s.erase("A");
    s.insert("A","a");
    s.insert("A","a");
    s.insert("A","a");
    cout << s << endl;
    s.erase("A");
    s.erase("A");
    s.erase("A");
    cout << "should be blank" << s << endl;
    assert(s.begin() == s.end());
    assert(s.size() == 0);

    s.insert("M", "M");
    s.insert("N", "N");
    s.insert("K", "K");
    cout << s << endl;
    s.erase("M");
    cout << s << endl;
    s.erase("K");
    cout << s << endl;
    s.erase("N");
    cout << s << endl;
    assert(s.size() == 0);

    s.insert("5", "M");
    s.insert("8", "N");
    s.insert("7", "K");
    s.insert("6", "W");

    cout << s << endl;
    s.erase("5");
    cout << s << endl;

    insertBalancedKeys(s);
    cout << "==========================================" << endl;
    cout << s << endl;
    s.erase("G");
    s.erase("T");
    s.erase("L");
    s.erase("B");
    s.erase("Y");
    s.erase("7");
    s.erase("6");
    s.erase("U");
    assert(s.find("G") == s.end());
    assert(s.find("T") == s.end());
    assert(s.find("L") == s.end());
    assert(s.find("B") == s.end());
    assert(s.find("Y") == s.end());
    assert(s.find("7") == s.end());
    assert(s.find("6") == s.end());
    assert(s.find("42") == s.end());
    assert(s.find("8") != s.end());
    cout << "==========================================" << endl;
    cout << s << endl;

    cout << s["E"] << endl;
    s["new key"] = "new value";
    cout << s["new key"] << endl;
    s["E"] = "new value for an existing key";
    cout << s["E"] << endl;
    return 0;
}
