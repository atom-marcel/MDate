
/**
* MDate.h
* 
* Diese Headerdatei sorgt für die Implementierung 
* einer Klasse die für Datum- und Zeiterfassung 
* zuständig ist.
*/
#ifndef MDATE_H
#define MDATE_H

#include <iostream>
#include <vector>
#include <functional>


/**
* Diese Klasse bietet verschiedene Funktionen um ein
* Datum zu erfassen, darzustellen und wiederzugeben.
*/
class Date
{
private:
    const int TIMESTAMP_FROM = 1970;
    
    uint64_t ms = 0;

    bool leapyear;

    int year;
    int month;
    int day;
    int day_month;
    int hour;
    int minute;
    int second;
    int weekday;
    int week_of_year;

    /**
    * Hilfsfunktion zum Berechnen des Wochentages dabei gilt "Sonntag = 0, Montag = 1, ... 
    * Samstag = 6".
    * 
    * @param d Der aktuelle Tag des Monats.
    * @param m Der aktuelle Monat (angefangen bei 0 = Januar).
    * @param y Das aktuelle Jahr.
    */
    int Evaluate_weekday(int d, int m, int y);
    int Evaluate_week_of_year();
    int Find_first_weekday();
    void Evaluate_Units();
    void Time_Deviation(int input, int min_value, int max_value, int& time_attr, int& next_time_attr, void(*fptr)(void*, int), void* context);
    void Evaluate_DayInYear();
    void EvaluateStaticDate();
    void Evaluate_Milliseconds();

public:
    std::vector<int> month_days{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; /**< Vektor der die maximale Anzahl der Tage des jeweiligen Monats als Index abbildet. Beim Schaltjahr wird auch der Februar von 28 auf 29 maximalen Tagen geändert, dies geschieht im weiteren Quellcode.*/
    std::vector<std::string> de_weekday_string{ "Sonntag", "Montag", "Dienstag", "Mittwoch", "Donnerstag", "Freitag", "Samstag" }; /**< Vektor der die jeweiligen Wochentag ausgeschrieben abbildet. Es wird dabei die deutsche Sprache verwendet.*/

    /**
    * Konstruktor der die aktuellen Zeitstempel in ein Datum umwandelt.
    */
	Date();
    /**
    * Konstruktor bei dem ein beliebiges Datum ausgewählt werden kann.
    * @param y Jahr
    * @param m Monat
    * @param d Tag im Monat
    * @param h Stunde
    * @param min Minute
    * @param s Sekunde
    */
	Date(int y, int m, int d, int h, int min, int s);
    /**
    * Zum Berechnen der aktuellen deutschen Zeitzone. Dabei wird auch Winter- und 
    * Sommerzeit berücksichtigt.
    */
    void German_GMT();
    /**
    * Gibt die Millisekunden die ab dem 01.01.1970 vergangen sind, als string zurück.
    */
    std::string Ms_Str();
    /**
    * Gibt das Datum in der Kommandozeile aus.
    */
    void Print_Date();
    /**
    * Inkrementiert den Monatstag.
    */
    void Month_Day_Increment();
    /**
    * Dekrementiert den Monatstag.
    */
    void Month_Day_Decrement();

    // Getter Section
    /**
    * Gibt das Datum im Format 'YYYY-MM-DDTHH:mm:ss' zurück.
    * YYYY : Jahr
    * MM : Monat (zweistellige) 
    * DD : Tag im Monat (zweistellige)
    * HH : Stunde (zweistellige)
    * mm : Minute (zweistellige)
    * ss : Sekunde (zweistellig)
    */
    std::string Get_Date();
    int Get_Year();
    /**
    * Gibt den Monat zurück, dabei wird von 0 an gezählt. Also gilt 0<=x<=11.
    * 0 : Januar
    * 1 : Februar
    * 2 : März
    * 3 : April
    * 4 : Mai
    * 5 : Juni
    * 6 : Juli
    * 7 : August
    * 8 : September
    * 9 : Oktober
    * 10 : November
    * 11 : Dezember
    */
    int Get_Month();
    int Get_MonthDay();
    int Get_Hour();
    int Get_Minute();
    int Get_Second();
    /**
    * Gibt den Wochentag zurück. Dabei gilt 0<=x<=6.
    * 0 : Sonntag
    * 1 : Montag
    * 2 : Dienstag 
    * 3 : Mittwoch
    * 4 : Donnerstag
    * 5 : Freitag
    * 6 : Samstag
    */
    int Get_Weekday();
    int Get_Week_of_year();
    uint64_t Get_Milliseconds();

    // Setter Section
    /**
    * Legt das Jahr fest. Dabei sollte das Jahr 1970 nicht unterschreiten, sonst kann es zu
    * Fehlern im Quellcode führen, da mit unsigned Integer gearbeitet wird.
    * 
    * @param in_year Jahr
    */
    void Set_Year(int in_year);
    /**
    * Legt den Monat fest. Dabei ist zu achten, dass man bei 0 anfängt die Monate zu zählen.
    * Also 0 = Januar, 1 = Februar ... 11 = Dezember, 12 = Januar, -1 = Dezember
    * 
    * @param in_month Monat 
    */
    void Set_Month(int in_month);
    void Set_MonthDay(int in_day_month);
    void Set_Hour(int in_hour);
    void Set_Minute(int in_minute);
    void Set_Second(int in_second);
    void Set_Milliseconds(uint64_t milliseconds);

};

#endif