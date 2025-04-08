#include <iostream>
#include <memory>
using namespace std;

class Document {
public:
    virtual void display() = 0;
    virtual ~Document() = default;
};

class RealDocument : public Document {
private:
    string filename;

public:
    explicit RealDocument(const string& filename) : filename(filename) {
        documentForWho();
    }

    void display() override {
        cout << "Displaying: " << filename << endl;
    }

    void documentForWho() {
        cout << "Access given to: " << filename << endl;
    }
};

class SecureDocumentProxy : public Document {
private:
    shared_ptr<RealDocument> realDocument;
    string filename;
    string who;

public:
    SecureDocumentProxy(const string& filename, const string& who) : filename(filename), who(who) {}

    void display() override {
        if (!realDocument) {
            realDocument = make_shared<RealDocument>(filename);
        }
        cout << "Accessing document as: " << who << endl;
        realDocument->display();
    }
};

int main() {
    SecureDocumentProxy documentForAdmin("Admin_Document.txt", "admin");
    SecureDocumentProxy documentForManager("Manager_Document.txt", "manager");
    SecureDocumentProxy documentForGuest("Guest_Document.txt", "guest");

    cout << "admin" << endl;
    documentForAdmin.display();

    cout << "manager" << endl;
    documentForManager.display();

    cout << "guest" << endl;
    documentForGuest.display();

    return 0;
}
