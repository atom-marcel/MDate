// MDate.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "MDate.h"

int test_count = 0;
int test_failed = 0;

bool TestCompare(std::string c1, std::string c2) {
    test_count++;
    if (c1 == c2) {
        std::cout << "Test " << test_count << " passed." << std::endl;
    }
    else {
        std::cout << "Test " << test_count << " failed!" << std::endl;
        std::cout << "'" << c1 << "'" << " is not eqal " << "'" << c2 << "'" << std::endl;
        test_failed++;
    }
    return c1 == c2;
}

bool TestCompare(int c1, int c2) {
    test_count++;
    if (c1 == c2) {
        std::cout << "Test " << test_count << " passed." << std::endl;
    }
    else {
        std::cout << "Test " << test_count << " failed!" << std::endl;
        std::cout << "'" << c1 << "'" << " is not eqal " << "'" << c2 << "'" << std::endl;
        test_failed++;
    }
    return c1 == c2;
}

bool TestCompare(uint16_t c1, uint16_t c2) {
    test_count++;
    if (c1 == c2) {
        std::cout << "Test " << test_count << " passed." << std::endl;
    }
    else {
        std::cout << "Test " << test_count << " failed!" << std::endl;
        std::cout << "'" << c1 << "'" << " is not eqal " << "'" << c2 << "'" << std::endl;
        test_failed++;
    }
    return c1 == c2;
}


void TestMDate() {
    // Current Timestamp

    // Custom Dates
    Date* testDate2 = new Date(2019, 0, 1, 0, 0, 0);
    TestCompare(testDate2->Get_Date(), "2019-01-01T00:00:00");
    testDate2->Month_Day_Decrement();
    TestCompare(testDate2->Get_Date(), "2018-12-31T00:00:00");
    testDate2->Month_Day_Increment();
    TestCompare(testDate2->Get_Date(), "2019-01-01T00:00:00");
    testDate2->Set_Hour(24);
    TestCompare(testDate2->Get_Date(), "2019-01-02T00:00:00");
    testDate2->Set_Hour(26);
    TestCompare(testDate2->Get_Date(), "2019-01-03T02:00:00");

    testDate2->Set_Hour(-6);
    TestCompare(testDate2->Get_Date(), "2019-01-02T20:00:00");
    testDate2->Set_Hour(-48);
    TestCompare(testDate2->Get_Date(), "2018-12-31T20:00:00");
    testDate2->Set_Hour(0);
    TestCompare(testDate2->Get_Date(), "2018-12-31T00:00:00");
    testDate2->Set_Hour(24);
    TestCompare(testDate2->Get_Date(), "2019-01-01T00:00:00");
    Date* testDate3 = new Date(2022, 1, 28, 0, 0, 0);
    testDate3->Month_Day_Increment();
    TestCompare(testDate3->Get_Date(), "2022-03-01T00:00:00");

    Date* testDate4 = new Date(2020, 1, 28, 0, 0, 0);
    testDate4->Month_Day_Increment();
    TestCompare(testDate4->Get_MonthDay(), 29);
    testDate4->Month_Day_Increment();
    TestCompare(testDate4->Get_Date(), "2020-03-01T00:00:00");
    testDate4->Set_Minute(-20);
    TestCompare(testDate4->Get_Date(), "2020-02-29T23:40:00");
    testDate4->Set_Minute(120);
    TestCompare(testDate4->Get_Date(), "2020-03-01T01:00:00");
    TestCompare(testDate4->Get_Week_of_year(), 9);
    TestCompare(testDate4->Get_Weekday(), 0);

    testDate4->Set_Second(20);
    TestCompare(testDate4->Get_Date(), "2020-03-01T01:00:20");
    testDate4->Set_Second(-40);
    TestCompare(testDate4->Get_Date(), "2020-03-01T00:59:40");
    testDate4->Set_Second(60);
    TestCompare(testDate4->Get_Date(), "2020-03-01T01:00:00");
    testDate4->Set_Second(180);
    TestCompare(testDate4->Get_Date(), "2020-03-01T01:03:00");

    Date* testDate5 = new Date(2022, 0, 1, 0, 0, 0);
    TestCompare(testDate5->Ms_Str(), "1640995200000");

    testDate5->Set_Milliseconds(1646006400000);
    TestCompare(testDate5->Get_Date(), "2022-02-28T00:00:00");
    testDate5->Month_Day_Increment();
    TestCompare(testDate5->Get_Date(), "2022-03-01T00:00:00");

    std::cout << test_count - test_failed << " out of " << test_count << " Tests passed." << std::endl;
}

int main()
{
    TestMDate();
    Date* date = new Date();
    date->Print_Date();
    std::system("pause");
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
