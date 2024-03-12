#include <iostream>
#include <unistd.h>
#include <mysql.h>

using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "root";

void progressBar(int width, int time) {
    for (int i = 0; i < width; ++i) {
        cout << "[";

        for (int j = 0; j <= i; ++j) {
            cout << "=";
        }

        for (int j = i + 1; j < width; ++j) {
            cout << " ";
        }

        cout << "] " << int((float)(i + 1) / width * 100) << "%\r";
        cout.flush();

        // Simulate some work
        usleep(time * 1000); // usleep takes time in microseconds
    }

    cout << endl;
}

bool insertRecord(MYSQL* obj, int College_ID, const char* Name, const char* BirthDate, float Grade) {
    char query[200];
    sprintf(query, "INSERT INTO student(College_ID, Name, BirthDate, Grade) VALUES(%d, '%s', '%s', %f)", College_ID, Name, BirthDate, Grade);
    if (mysql_query(obj, query)) {
        cout << "Error: " << mysql_error(obj) << endl;
        return false;
    }
    return true;
}

int main() {
    MYSQL* obj;
    int ProgramIsOpened = true;

    if (!(obj = mysql_init(0))) {
        cout << "ERROR: MYSQL object could not be created." << endl;
        return 1;
    }

    if (!mysql_real_connect(obj, HOST, USER, PASS, "school", 3306, NULL, 0)) {
        cout << "ERROR: Some database info is wrong or do not exist." << endl;
        cout << mysql_error(obj) << endl;
        return 1;
    }

    cout << "Logged in." << endl << endl;

    while (ProgramIsOpened) {
        // Insertion
        int College_ID;
        char Name[20];
        char BirthDate[11];
        float Grade;

        cout << "College ID: ";
        cin >> College_ID;
        cin.ignore(100, '\n');

        cout << "Name: ";
        cin.getline(Name, 20, '\n');

        cout << "BirthDate: ";
        cin.getline(BirthDate, 11, '\n');

        cout << "Grade: ";
        cin >> Grade;
        cin.ignore(100, '\n');

        if (insertRecord(obj, College_ID, Name, BirthDate, Grade)) {
            cout << "Record added successfully." << endl;
        }

        // Sequential access
        if (mysql_query(obj, "SELECT * FROM student")) {
            cout << "Error: " << mysql_error(obj) << endl;
            return 1;
        }

        MYSQL_RES* result = mysql_store_result(obj);

        if (result) {
            MYSQL_ROW row;
            cout << "Retrieved records:" << endl;
            while ((row = mysql_fetch_row(result))) {
                cout << "College ID: " << row[0] << ", Name: " << row[1] << ", BirthDate: " << row[2] << ", Grade: " << row[3] << endl;
            }
            mysql_free_result(result);
        } else {
            cout << "Error: Could not retrieve result set." << endl;
        }

        cout << endl << "Another?" << endl;
        cout << "[1]: Yes" << endl;
        cout << "[0]: No" << endl;
        cout << "Answer: ";
        cin >> ProgramIsOpened;
        cout << endl;
    }

    cout << "BYE!!!!" << endl;
    return 0;
}
