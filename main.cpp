#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class Media{
public:
    bool keep_updating;
    string type; ///whether it's a movie or tv show
    int points; /// points keep updating based on quiz
    double rating; ///quality rating
    string maturity; ///maturity rating
    int year; ///year released
    string genre;
    string title;

    ///when initializing, have to check if the value is null
    Media(string type, double rating, string maturity, int year, string genre, string title){
        this->keep_updating = true;
        this->type = type;
        this->points = 0;
        this->rating = rating;
        this->maturity = maturity;
        this->year = year;
        this->genre = genre;
        this->title = title;
    }

    void NoMoreUpdate(){
        keep_updating = false;
    }

    void AddPoints(int num){
        points += num;
    }

};

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    string filePath = "C://Users//skodi//CLionProjects//Project3//Project3_xcel.csv";
    ifstream file(filePath); // Open the CSV file
    string line;

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }
    getline(file, line);

    vector<Media> media;
    // Read and process each line
    while (getline(file, line)) {
        vector<string> fields = split(line, ',');

        string type = fields[1];
        double rating = stod(fields[7]);
        string maturity = fields[9]; ///maturity rating
        int year = stoi(fields[4]);
        string genre = fields[10];
        string title = fields[2];

        Media curr_media(type, rating, maturity, year, genre, title);
        media.push_back(curr_media);
    }

    file.close(); // Close the file

    ///Start the game

    cout << "Movie Night Conundrum" << endl;
    cout << "Let us help you decide what to watch tonight! Take a short seven question quiz, and we'll give you your top 5 recommendations. Enter S to start!" << endl;
    string start;
    cin >> start;
    while (start != "S"){
        cout << "You did not hit the correct key. To start the quiz, enter S" << endl;
        cin >> start;
    }

    ///Question 1: Movie or TV Show
    cout << "Question 1:" << endl;
    cout << "What type of media do you want to watch? Enter your letter choice." << endl;
    cout << "A. Movie" << endl << "B. TV Show" << endl;
    string type;
    string answer;
    cin >> answer;
    while (answer != "A" && answer != "B"){
        cout << "Not a valid choice. You may either type A or B. Try again" << endl;
        cin >> answer;
    }

    if (answer == "A"){
        type = "movie";
        for (Media title : media){
            if (title.type == "tvSeries"){
                title.NoMoreUpdate();
            }
        }
    }

    if (answer == "B"){
        type = "show";
        for (Media title : media){
            if (title.type == "movie"){
                title.NoMoreUpdate();
            }
        }
    }

    ///Question 2: enjoyment rating
    cout << "What is the minimum enjoyment rating you are willing to watch. Enter an integer between 0 and 10." << endl;
    cin >> answer;
    bool is_it_corr = false;
    int value;

    while (is_it_corr == false){
        try {
            value = stoi(answer);
            is_it_corr = true;

            if (value < 0 || value > 10) {
                cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
                is_it_corr = false;
                cin >> answer;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
            cin >> answer;
        }
        catch (const out_of_range& e) {
            cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
            cin >> answer;
        }

    }

    for (Media title : media){
        if (title.keep_updating == true && title.rating < value){
            title.NoMoreUpdate();
        }
    }

    ///Question 3: scripted vs non-scripted
    cout << "Do you want the content to be:" << endl;
    cout << "A. Scripted" << endl;
    cout << "B. Non-Scripted" << endl;
    cin >> answer;
    string type2;
    while (answer != "A" && answer != "B"){
        cout << "Not a valid choice. You may either type A or B. Try again" << endl;
        cin >> answer;
    }

    if (answer == "A"){
        type2 = "scripted";
        for (Media title : media){
            if (title.keep_updating == true && (title.genre == "Game-Show" || title.genre == "News" || title.genre == "Reality-TV" || title.genre == "Sport" || title.genre == "Talk-Show")){
                title.NoMoreUpdate();
            }
        }
    }

    if (answer == "B"){
        type2 = "nonscripted";
        for (Media title : media){
            if (title.keep_updating == true && title.genre != "Game-Show" && title.genre != "News" && title.genre != "Reality-TV" && title.genre != "Sport" && title.genre != "Talk-Show"){
                title.NoMoreUpdate();
            }
        }
    }

    ///Question 4: highest maturity
    cout << "What is the highest maturity level that you are willing to watch?" << endl;
    if (type == "movie"){
        cout << "A. G" << endl;
        cout << "B. PG" << endl;
        cout << "C. PG-13" << endl;
        cout << "D. R" << endl;
        cout << "E. NC-17" << endl;
        cin >> answer;

        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E"){
            cout << "Not a valid choice. You may either type A or B or C or D or E. Try again" << endl;
            cin >> answer;
        }

        if (answer == "A"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "PG" || title.maturity == "PG-13" || title.maturity == "R" || title.maturity == "NC-17"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }

        if (answer == "B"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "PG-13" || title.maturity == "R" || title.maturity == "NC-17"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }

        if (answer == "C"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "R" || title.maturity == "NC-17"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }

        if (answer == "D"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "NC-17"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
    }

    if (type == "show"){
        cout << "A. TV-Y" << endl;
        cout << "B. TV-Y7" << endl;
        cout << "C. TV-G" << endl;
        cout << "D. TV-PG" << endl;
        cout << "E. TV-14" << endl;
        cout << "F. TV-MA" << endl;
        cin >> answer;

        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E" && answer != "F"){
            cout << "Not a valid choice. You may either type A or B or C or D or E or F. Try again" << endl;
            cin >> answer;
        }

        if (answer == "A"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "TV-Y7" || title.maturity == "TV-G" || title.maturity == "TV-PG" || title.maturity == "TV-14"|| title.maturity == "TV-MA"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
        if (answer == "B"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "TV-G" || title.maturity == "TV-PG" || title.maturity == "TV-14"|| title.maturity == "TV-MA"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
        if (answer == "C"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "TV-PG" || title.maturity == "TV-14"|| title.maturity == "TV-MA"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
        if (answer == "D"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "TV-14"|| title.maturity == "TV-MA"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
        if (answer == "E"){
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "TV-MA"){
                        title.NoMoreUpdate();
                    }
                }
            }
        }
    }

    ///Question 5: What is your preferred maturity rating?
    cout << "What is your preferred maturity rating?" << endl;
    if (type == "movie") {
        cout << "A. G" << endl;
        cout << "B. PG" << endl;
        cout << "C. PG-13" << endl;
        cout << "D. R" << endl;
        cout << "E. NC-17" << endl;
        cin >> answer;

        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E") {
            cout << "Not a valid choice. You may either type A or B. Try again" << endl;
            cin >> answer;
        }

        if (answer == "A") {
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "G"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "PG"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "PG-13"){
                        title.AddPoints(2);
                    }
                }
            }
        }

        if (answer == "B") {
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "PG"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "G"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "PG-13"){
                        title.AddPoints(2);
                    }
                }
            }
        }

        if (answer == "C") {
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "PG-13"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "PG" || title.maturity == "R"){
                        title.AddPoints(2);
                    }
                }
            }
        }

        if (answer == "D") {
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "R"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "NC-17"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "PG-13"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "E") {
            for (Media title : media){
                if (title.keep_updating == true){
                    if (title.maturity == "NC-17"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "R"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "PG-13"){
                        title.AddPoints(2);
                    }
                }
            }
        }



    }

    if (type == "show"){
        cout << "A. TV-Y" << endl;
        cout << "B. TV-Y7" << endl;
        cout << "C. TV-G" << endl;
        cout << "D. TV-PG" << endl;
        cout << "E. TV-14" << endl;
        cout << "F. TV-MA" << endl;
        cin >> answer;

        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E" && answer != "F"){
            cout << "Not a valid choice. You may either type A or B. Try again" << endl;
            cin >> answer;
        }

        if (answer == "A") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-Y"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-Y7" || title.maturity == "TV-G"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-14"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "B") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-Y7"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-Y" || title.maturity == "TV-G"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-14"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "C") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-G"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-Y" || title.maturity == "TV-Y7" || title.maturity == "TV-14"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-14"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "D") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-PG"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-G" || title.maturity == "TV-14"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-Y7"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "E") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-14"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-PG" || title.maturity == "TV-MA"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-G"){
                        title.AddPoints(2);
                    }
                }
            }
        }
        if (answer == "F") {
            for (Media title: media) {
                if (title.keep_updating == true) {
                    if (title.maturity == "TV-MA"){
                        title.AddPoints(10);
                    }
                    if (title.maturity == "TV-14"){
                        title.AddPoints(5);
                    }
                    if (title.maturity == "TV-PG"){
                        title.AddPoints(2);
                    }
                }
            }
        }
    }

    ///Question 6: what decade
    cout << "What decade do you want the media to be from?" << endl;
    cout << "A. 1969 and before" << endl;
    cout << "B. 1970s" << endl;
    cout << "C. 1980s" << endl;
    cout << "D. 1990s" << endl;
    cout << "E. 2000s" << endl;
    cout << "F. 2010s" << endl;
    cout << "G. 2020s" << endl;
    cin >> answer;

    while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E" && answer !="F" && answer !="G"){
        cout << "Not a valid choice. You may either type A or B or C or D or E or F or G. Try again" << endl;
        cin >> answer;
    }

    if (answer == "A"){
        for (Media title : media){
            if (title.year < 1970){
                title.AddPoints(10);
            }
            else if (title.year < 1980){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "B"){
        for (Media title : media){
            if (1969 < title.year && title.year < 1980){
                title.AddPoints(10);
            }
            else if (1979 < title.year && title.year < 1990){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "C"){
        for (Media title : media){
            if (1979 < title.year && title.year < 1990){
                title.AddPoints(10);
            }
            else if ((1989 < title.year && title.year < 2000 ) || (1969 < title.year && title.year < 1980)){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "D"){
        for (Media title : media){
            if (1989 < title.year && title.year < 2000){
                title.AddPoints(10);
            }
            else if ((1999 < title.year && title.year < 2010 ) || (1979 < title.year && title.year < 1990)){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "E"){
        for (Media title : media){
            if (1999 < title.year && title.year < 2010){
                title.AddPoints(10);
            }
            else if ((2009 < title.year && title.year < 2020 ) || (1989 < title.year && title.year < 2000)){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "F"){
        for (Media title : media){
            if (2009 < title.year && title.year < 2020){
                title.AddPoints(10);
            }
            else if ((2019 < title.year ) || (1999 < title.year && title.year < 2010)){
                title.AddPoints(5);
            }
        }
    }

    if (answer == "G"){
        for (Media title : media){
            if (2019 < title.year){
                title.AddPoints(10);
            }
            else if ((2009 < title.year && title.year < 2020)){
                title.AddPoints(5);
            }
        }
    }

    ///Question 7: Preferred genre
    if (type2 == "nonscripted"){
        cout << "What is your preferred genre?" << endl;
        cout << "A. Game-Show" << endl;
        cout << "B. News" << endl;
        cout << "C. Reality-TV" << endl;
        cout << "D. Sport" << endl;
        cout << "E. Talk-Show" << endl;
        cin >> answer;
        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E"){
            cout << "Not a valid choice. You may either type A or B or C or D or E. Try again" << endl;
            cin >> answer;
        }

        for (Media title  : media){
            if (title.keep_updating == true){
                if (answer == "A"){
                    if (title.genre == "Game-Show"){
                        title.AddPoints(10);
                    }
                }
                if (answer == "B"){
                    if (title.genre == "News"){
                        title.AddPoints(10);
                    }
                }
                if (answer == "C"){
                    if (title.genre == "Reality-TV"){
                        title.AddPoints(10);
                    }
                }
                if (answer == "D"){
                    if (title.genre == "Sport"){
                        title.AddPoints(10);
                    }
                }
                if (answer == "E"){
                    if (title.genre == "Talk-Show"){
                        title.AddPoints(10);
                    }
                }
            }
        }

    }

    if (type2 == "scripted") {
        cout << "What is your preferred genre? Pick a Category" << endl;
        cout << "A. Biography, Documentary, Crime, History, War, Western" << endl;
        cout << "B. Film-Noir" << endl;
        cout << "C. Music, Musical" << endl;
        cout << "D. Action, Adventure, Thriller, Fantasy, Horror, Mystery, Sci-Fi" << endl;
        cout << "E. Romance, Comedy" << endl;
        cout << "F. Animation" << endl;
        cout << "G. Family" << endl;
        cout << "H. Mystery" << endl;
        cin >> answer;
        while (answer != "A" && answer != "B" && answer != "C" && answer != "D" && answer != "E") {
            cout << "Not a valid choice. You may either type A or B or C or D or E. Try again" << endl;
            cin >> answer;
        }

        for (Media title: media) {
            if (title.keep_updating == true) {
                if (answer == "A") {
                    vector <string> genres = {"Biography", "Documentary", "Crime", "History", "War", "Western"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                    cout << "Type your preferred genre in that category as displayed" << endl;
                    cin >> answer;
                    while (find(genres.begin(), genres.end(), answer) == genres.end()) {
                        cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                        cin >> answer;
                    }
                    if (title.genre == answer) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "B") {
                    vector <string> genres = {"Film-Noir"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(10);
                    }
                }
                if (answer == "C") {
                    vector <string> genres = {"Music","Musical"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                    cout << "Type your preferred genre in that category as displayed." << endl;
                    cin >> answer;
                    while (find(genres.begin(), genres.end(), answer) == genres.end()) {
                        cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again." << endl;
                        cin >> answer;
                    }
                    if (title.genre == answer) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "D") {
                    vector <string> genres = {"Action", "Adventure", "Thriller", "Fantasy", "Horror", "Mystery", "Sci-Fi"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                    cout << "Type your preferred genre in that category as displayed" << endl;
                    cin >> answer;
                    while (find(genres.begin(), genres.end(), answer) == genres.end()) {
                        cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                        cin >> answer;
                    }
                    if (title.genre == answer) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "E") {
                    vector<string> genres = {"Romance", "Comedy"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                    cout << "Type your preferred genre in that category as displayed" << endl;
                    cin >> answer;
                    while (find(genres.begin(), genres.end(), answer) == genres.end()) {
                        cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                        cin >> answer;
                    }
                    if (title.genre == answer) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "F") {
                    vector <string> genres = {"Animation"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "G") {
                    vector <string> genres = {"Family"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                }
                if (answer == "H") {
                    vector <string> genres = {"Mystery"};
                    if (find(genres.begin(), genres.end(), title.genre) != genres.end()) {
                        title.AddPoints(5);
                    }
                }

            }
        }
    }

    ///add print functions here to display sorting


    return 0;
}
