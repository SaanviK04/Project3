#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iomanip>
using namespace std;

class Media {
public:
    string type; ///whether it's a movie or tv show
    int points; /// points keep updating based on quiz
    double rating; ///quality rating
    string maturity; ///maturity rating
    int year; ///year released
    string yearString;
    string genre;
    string title;


    // Default constructor
    Media()
        : type(""), points(0), rating(0.0), maturity(""), year(0), yearString(""), genre(""), title("") {}

    ///when initializing, have to check if the value is null
    Media(string type, double rating, string maturity, int year, string yearString, string genre, string title) {
        this->type = type;
        this->points = 0;
        this->rating = rating;
        this->maturity = maturity;
        this->year = year;
        this->yearString = yearString;
        this->genre = genre;
        this->title = title;
    }

    void AddPoints(int num) {
        points += num;
    }

};

void merge(vector<Media>& media, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary vectors to hold the split sections
    vector<Media> L(n1);
    vector<Media> R(n2);

    // Copying data to temporary vectors
    for (int i = 0; i < n1; i++)
        L[i] = media[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = media[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].points >= R[j].points) { // Sorting by points
            media[k] = L[i];
            i++;
        }
        else {
            media[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        media[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        media[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Media>& media, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(media, left, mid);
        mergeSort(media, mid + 1, right);
        merge(media, left, mid, right);
    }
}

int partition(vector<Media>& media, int low, int high) {
    int pivot = media[high].points;
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (media[j].points > pivot) { // Sort in descending order by points
            i++;
            swap(media[i], media[j]);
        }
    }
    swap(media[i + 1], media[high]);

    return (i + 1);
}

void quickSort(vector<Media>& media, int low, int high) {
    if (low < high) {
        int pi = partition(media, low, high);
        // cout << "DEBUG: Partition index: " << pi << ", Low: " << low << ", High: " << high << endl;
        quickSort(media, low, pi - 1);
        quickSort(media, pi + 1, high);
    }
}
////////////////////////

//Loading bar attempt
void displayLoadingBar(int progress, int total) {
    int barWidth = 36;
    float ratio = static_cast<float>(progress) / total;
    int filledWidth = static_cast<int>(barWidth * ratio);

    cout << "\r[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) cout << "=";
        else if (i == filledWidth) cout << ">";
        else cout << " ";
    }
    cout << "] " << int(ratio * 100.0) << "%" << flush;
}

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
    string filePath = "Project3_xcel.csv"; //C://Users//skodi//CLionProjects//Project3//Project3_xcel.csv";
    ifstream file(filePath); // Open the CSV file
    string line;

    if (!file.is_open()) { // If file cannot open then program end with code 1
        cerr << "Could not open the file!\n";
        return 1;
    }

    string userInput;
    string userInput2;
    string userFormatType;
    int userMinimumRating;
    string userGenreType;
    vector<string> userGenres;
    vector<string> badMaturityRatings;

    cout 
        << " ::::    ::::: ::::    :::  ::::::::  \n"
        << " +:+:+: :+:+:+ :+:+:   :+: :+:    :+: \n"
        << " +:+ +:+:+ +:+ :+:+:+  +:+ +:+        \n"
        << " +#+  +:+  +#+ +#+ +:+ +#+ +#+        \n"
        << " +#+       +#+ +#+  +#+#+# +#+        \n"
        << " #+#       #+# #+#   #+#+# #+#    #+# \n"
        << " ###       ### ###    ####  ########  \n"
        << "--------------------------------------\n"
        << "|       Movie Night Conundrum!       |\n"
        << "--------------------------------------\n"
        << "Let us help you decide what to watch tonight!\n"
        << "Take a short seven question quiz, and we'll give you your top 5 recommendations. Enter S to start!\n";
    cin >> userInput;
    while (userInput != "S") {
        cout << "You did not hit the correct key. To start the quiz, enter S" << endl;
        cin >> userInput;
    }

    // Question 1: Movie or TV Show
    cout << "--------------------------------------\n"
        << "|             Question 1             |\n"
        << "--------------------------------------\n"
        << "What type of media do you want to watch? Enter your letter choice.\n"
        << "A. Movie\n"
        << "B. TV Show\n";
    cin >> userInput;
    while (userInput != "A" && userInput != "B") {
        cout << "Not a valid choice. You may either type A or B. Try again\n";
        cin >> userInput;
    }

    if (userInput == "A") { userFormatType = "movie"; }
    else if (userInput == "B") { userFormatType = "tvSeries"; }

    // Question 2: enjoyment rating
    cout << "--------------------------------------\n"
        << "|             Question 2             |\n"
        << "--------------------------------------\n"
        << "What is the minimum enjoyment rating you are willing to watch. Enter an integer between 0 and 10.\n";
    cin >> userInput;
    bool is_it_corr = false;

    while (is_it_corr == false) {
        try {
            userMinimumRating = stoi(userInput);
            is_it_corr = true;

            if (userMinimumRating < 0 || userMinimumRating > 10) {
                cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
                is_it_corr = false;
                cin >> userInput;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
            cin >> userInput;
        }
        catch (const out_of_range& e) {
            cout << "Not a valid response. Type an integer between 0 and 10. Try again" << endl;
            cin >> userInput;
        }
    }

    // Question 3: scripted vs non-scripted
    cout << "--------------------------------------\n"
        << "|             Question 3             |\n"
        << "--------------------------------------\n"
        << "Do you want the content to be:\n"
        << "A. Scripted\n"
        << "B. Non-Scripted\n";
    cin >> userInput;
    while (userInput != "A" && userInput != "B") {
        cout << "Not a valid choice. You may either type A or B. Try again\n";
        cin >> userInput;
    }

    if (userInput == "A") {
        userGenreType = "scripted";
        userGenres = { "Action", "Adventure", "Animation", "Biography", "Comedy",
            "Crime", "Documentary", "Drama", "Family", "Fantasy",
            "Film-Noir", "History", "Horror", "Music", "Musical",
            "Mystery", "Romance", "Sci-Fi", "Short", "Thriller",
            "War", "Western" };
    }
    else if (userInput == "B") {
        userGenreType = "nonscripted";
        userGenres = { "Game-Show", "News", "Reality-TV", "Sport", "Talk-Show" };
    }

    // Question 4: highest maturity rating
    userInput = "";

    cout << "--------------------------------------\n"
        << "|             Question 4             |\n"
        << "--------------------------------------\n"
        << "What is the highest maturity level that you are willing to watch?\n";

    if (userFormatType == "movie") {
        cout << "A. G\n"
            << "B. PG\n"
            << "C. PG-13\n"
            << "D. R\n"
            << "E. NC-17\n";
        cin >> userInput;
        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E") {
            cout << "Not a valid choice. You may either type A, B, C, D, or E. Try again\n";
            cin >> userInput;
        }

        if (userInput == "A") { badMaturityRatings = { "PG", "PG-13", "R", "NC-17" }; }
        else if (userInput == "B") { badMaturityRatings = { "PG-13", "R", "NC-17" }; }
        else if (userInput == "C") { badMaturityRatings = { "R", "NC-17" }; }
        else if (userInput == "D") { badMaturityRatings = { "NC-17" }; }
        else { badMaturityRatings = {}; }
    }

    else if (userFormatType == "tvSeries") {
        cout << "A. TV-Y\n"
            << "B. TV-Y7\n"
            << "C. TV-G\n"
            << "D. TV-PG\n"
            << "E. TV-14\n"
            << "F. TV-MA\n";
        cin >> userInput;
        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E" && userInput != "F") {
            cout << "Not a valid choice. You may either type A or B or C or D or E or F. Try again" << endl;
            cin >> userInput;
        }

        if (userInput == "A") { badMaturityRatings = { "TV-Y7", "TV-G", "TV-PG", "TV-14", "TV-MA" }; }
        else if (userInput == "B") { badMaturityRatings = { "TV-G", "TV-PG", "TV-14", "TV-MA" }; }
        else if (userInput == "C") { badMaturityRatings = { "TV-PG", "TV-14", "TV-MA" }; }
        else if (userInput == "D") { badMaturityRatings = { "TV-14", "TV-MA" }; }
        else if (userInput == "E") { badMaturityRatings = { "TV-MA" }; }
        else { badMaturityRatings = {}; }
    }

    // Sort csv data based on absolute preferences above
    vector<Media> media;
    // Read and process each line
    getline(file, line);
    while (getline(file, line)) {
        vector<string> fields = split(line, ',');

        string type = fields[1];
        double rating = stod(fields[7]);
        string maturity = fields[9]; ///maturity rating
        if (maturity == "-1") { maturity = "No Maturity Rating"; }
        int year = stoi(fields[4]);
        string yearString = fields[4];
        if (yearString == "-1") { yearString = "Unknown"; }
        string genre = fields[10];
        string title = fields[2];

        // If the format type (movie/tvSeries), minimum rating, maturity rating, and genre preferences are met, then the media is added to the media vector
        if (userFormatType == type &&
            rating >= (userMinimumRating * 1.0) &&
            (find(badMaturityRatings.begin(), badMaturityRatings.end(), maturity) == badMaturityRatings.end()) &&
            (find(userGenres.begin(), userGenres.end(), genre) != userGenres.end())) {
            Media curr_media(type, rating, maturity, year, yearString, genre, title);
            media.push_back(curr_media);
        }
    }
    file.close(); // Close the file

    // Question 5: What is your preferred maturity rating?
    cout << "--------------------------------------\n"
        << "|             Question 5             |\n"
        << "--------------------------------------\n"
        << "What is your preferred maturity rating?" << endl;
    if (userFormatType == "movie") {
        cout << "A. G\n"
            << "B. PG\n"
            << "C. PG-13\n"
            << "D. R\n"
            << "E. NC-17\n";
        cin >> userInput;

        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E") {
            cout << "Not a valid choice. You may either type A or B. Try again" << endl;
            cin >> userInput;
        }

        if (userInput == "A") {
            for (Media& title : media) {
                if (title.maturity == "G") { title.AddPoints(10); }
                else if (title.maturity == "PG") { title.AddPoints(5); }
                else if (title.maturity == "PG-13") { title.AddPoints(2); }
            }
        }
        else if (userInput == "B") {
            for (Media& title : media) {
                if (title.maturity == "PG") { title.AddPoints(10); }
                else if (title.maturity == "G") { title.AddPoints(5); }
                else if (title.maturity == "PG-13") { title.AddPoints(2); }
            }
        }
        else if (userInput == "C") {
            for (Media& title : media) {
                if (title.maturity == "PG-13") { title.AddPoints(10); }
                else if (title.maturity == "PG" || title.maturity == "R") { title.AddPoints(2); }
            }
        }
        else if (userInput == "D") {
            for (Media& title : media) {
                if (title.maturity == "R") { title.AddPoints(10); }
                else if (title.maturity == "NC-17") { title.AddPoints(5); }
                else if (title.maturity == "PG-13") { title.AddPoints(2); }
            }
        }
        else if (userInput == "E") {
            for (Media& title : media) {
                if (title.maturity == "NC-17") { title.AddPoints(10); }
                else if (title.maturity == "R") { title.AddPoints(5); }
                else if (title.maturity == "PG-13") { title.AddPoints(2); }
            }
        }
    }

    else if (userFormatType == "tvSeries") {
        cout << "A. TV-Y" << endl;
        cout << "B. TV-Y7" << endl;
        cout << "C. TV-G" << endl;
        cout << "D. TV-PG" << endl;
        cout << "E. TV-14" << endl;
        cout << "F. TV-MA" << endl;
        cin >> userInput;
        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E" && userInput != "F") {
            cout << "Not a valid choice. You may either type A or B. Try again" << endl;
            cin >> userInput;
        }

        if (userInput == "A") {
            for (Media& title : media) {
                if (title.maturity == "TV-Y") { title.AddPoints(10); }
                if (title.maturity == "TV-Y7" || title.maturity == "TV-G") { title.AddPoints(5); }
                if (title.maturity == "TV-14") { title.AddPoints(2); }
            }
        }
        if (userInput == "B") {
            for (Media& title : media) {
                if (title.maturity == "TV-Y7") { title.AddPoints(10); }
                if (title.maturity == "TV-Y" || title.maturity == "TV-G") { title.AddPoints(5); }
                if (title.maturity == "TV-14") { title.AddPoints(2); }
            }
        }
        if (userInput == "C") {
            for (Media& title : media) {
                if (title.maturity == "TV-G") { title.AddPoints(10); }
                if (title.maturity == "TV-Y" || title.maturity == "TV-Y7" || title.maturity == "TV-14") { title.AddPoints(5); }
                if (title.maturity == "TV-14") { title.AddPoints(2); }
            }
        }
        if (userInput == "D") {
            for (Media& title : media) {
                if (title.maturity == "TV-PG") { title.AddPoints(10); }
                if (title.maturity == "TV-G" || title.maturity == "TV-14") { title.AddPoints(5); }
                if (title.maturity == "TV-Y7") { title.AddPoints(2); }
            }
        }
        if (userInput == "E") {
            for (Media& title : media) {
                if (title.maturity == "TV-14") { title.AddPoints(10); }
                if (title.maturity == "TV-PG" || title.maturity == "TV-MA") { title.AddPoints(5); }
                if (title.maturity == "TV-G") { title.AddPoints(2); }
            }
        }
        if (userInput == "F") {
            for (Media& title : media) {
                if (title.maturity == "TV-MA") { title.AddPoints(10); }
                if (title.maturity == "TV-14") { title.AddPoints(5); }
                if (title.maturity == "TV-PG") { title.AddPoints(2); }
            }
        }
    }

    // Question 6: what decade
    cout << "--------------------------------------\n"
        << "|             Question 6             |\n"
        << "--------------------------------------\n"
        << "What decade do you want the media to be from?\n"
        << "A. 1969 and before\n"
        << "B. 1970s\n"
        << "C. 1980s\n"
        << "D. 1990s\n"
        << "E. 2000s\n"
        << "F. 2010s\n"
        << "G. 2020s\n";
    cin >> userInput;
    while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E" && userInput != "F" && userInput != "G") {
        cout << "Not a valid choice. You may either type A or B or C or D or E or F or G. Try again" << endl;
        cin >> userInput;
    }

    if (userInput == "A") {
        for (Media& title : media) {
            if (title.year < 1970) { title.AddPoints(10); }
            if (title.year < 1980) { title.AddPoints(5); }
        }
    }
    else if (userInput == "B") {
        for (Media& title : media) {
            if (1969 < title.year && title.year < 1980) { title.AddPoints(10); }
            if (1979 < title.year && title.year < 1990) { title.AddPoints(5); }
        }
    }
    else if (userInput == "C") {
        for (Media& title : media) {
            if (1979 < title.year && title.year < 1990) { title.AddPoints(10); }
            if ((1989 < title.year && title.year < 2000) || (1969 < title.year && title.year < 1980)) { title.AddPoints(5); }
        }
    }
    else if (userInput == "D") {
        for (Media& title : media) {
            if (1989 < title.year && title.year < 2000) { title.AddPoints(10); }
            if ((1999 < title.year && title.year < 2010) || (1979 < title.year && title.year < 1990)) { title.AddPoints(5); }
        }
    }
    else if (userInput == "E") {
        for (Media& title : media) {
            if (1999 < title.year && title.year < 2010) { title.AddPoints(10); }
            if ((2009 < title.year && title.year < 2020) || (1989 < title.year && title.year < 2000)) { title.AddPoints(5); }
        }
    }
    else if (userInput == "F") {
        for (Media& title : media) {
            if (2009 < title.year && title.year < 2020) { title.AddPoints(10); }
            if ((2019 < title.year) || (1999 < title.year && title.year < 2010)) { title.AddPoints(5); }
        }
    }
    else if (userInput == "G") {
        for (Media& title : media) {
            if (2019 < title.year) { title.AddPoints(10); }
            if (2009 < title.year && title.year < 2020) { title.AddPoints(5); }
        }
    }

    // Question 7: Preferred genre
    cout << "--------------------------------------\n"
        << "|             Question 7             |\n"
        << "--------------------------------------\n";
    if (userGenreType == "nonscripted") {
        cout << "What is your preferred genre?\n"
            << "A. Game-Show\n"
            << "B. News\n"
            << "C. Reality-TV\n"
            << "D. Sport\n"
            << "E. Talk-Show\n";
        cin >> userInput;
        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" && userInput != "E") {
            cout << "Not a valid choice. You may either type A or B or C or D or E. Try again" << endl;
            cin >> userInput;
        }

        for (Media& title : media) {
            if (userInput == "A") {
                if (title.genre == "Game-Show") { title.AddPoints(15); }
            }
            else if (userInput == "B") {
                if (title.genre == "News") { title.AddPoints(15); }
            }
            else if (userInput == "C") {
                if (title.genre == "Reality-TV") { title.AddPoints(15); }
            }
            else if (userInput == "D") {
                if (title.genre == "Sport") { title.AddPoints(15); }
            }
            else if (userInput == "E") {
                if (title.genre == "Talk-Show") { title.AddPoints(15); }
            }
        }
    }

    else if (userGenreType == "scripted") {
        cout << "What is your preferred genre? Pick a Category\n"
            << "A. Biography, Documentary, Crime, History, War, Western\n"
            << "B. Film-Noir\n"
            << "C. Music, Musical\n"
            << "D. Action, Adventure, Thriller, Fantasy, Horror, Mystery, Sci-Fi\n"
            << "E. Romance, Comedy\n"
            << "F. Animation\n"
            << "G. Family\n"
            << "H. Mystery\n";
        cin >> userInput;
        while (userInput != "A" && userInput != "B" && userInput != "C" && userInput != "D" &&
            userInput != "E" && userInput != "F" && userInput != "G" && userInput != "H") {
            cout << "Not a valid choice. You may either type A or B or C or D or E. Try again" << endl;
            cin >> userInput;
        }


        if (userInput == "A") {

            vector <string> genres = { "Biography", "Documentary", "Crime", "History", "War", "Western" };
            cout << "Type your preferred genre in that category as displayed" << endl;
            cin >> userInput;
            while (find(genres.begin(), genres.end(), userInput) == genres.end()) {
                cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                cin >> userInput;
            }
            for (Media& title : media) {
                if (title.genre == userInput) { title.AddPoints(15); }
            }
        }
        else if (userInput == "B") {
            for (Media& title : media) {
                if (title.genre == "Film-Noir") { title.AddPoints(15); }
            }
        }
        else if (userInput == "C") {
            vector <string> genres = { "Music", "Musical" };
            cout << "Type your preferred genre in that category as displayed." << endl;
            cin >> userInput;
            while (find(genres.begin(), genres.end(), userInput) == genres.end()) {
                cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again." << endl;
                cin >> userInput;
            }
            for (Media& title : media) {
                if (title.genre == userInput) { title.AddPoints(15); }
            }
        }
        else if (userInput == "D") {
            vector <string> genres = { "Action", "Adventure", "Thriller", "Fantasy", "Horror", "Mystery", "Sci-Fi" };
            cout << "Type your preferred genre in that category as displayed" << endl;
            cin >> userInput;
            while (find(genres.begin(), genres.end(), userInput) == genres.end()) {
                cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                cin >> userInput;
            }
            for (Media& title : media) {
                if (title.genre == userInput) { title.AddPoints(15); }
            }
        }
        else if (userInput == "E") {
            vector<string> genres = { "Romance", "Comedy" };
            cout << "Type your preferred genre in that category as displayed" << endl;
            cin >> userInput;
            while (find(genres.begin(), genres.end(), userInput) == genres.end()) {
                cout << "Not a valid choice. Enter a genre name in the category you previously selected. Try again" << endl;
                cin >> userInput;
            }
            for (Media& title : media) {
                if (title.genre == userInput) { title.AddPoints(15); }
            }
        }
        else if (userInput == "F") {
            for (Media& title : media) {
                if (title.genre == "Animation") { title.AddPoints(15); }
            }
        }
        else if (userInput == "G") {
            for (Media& title : media) {
                if (title.genre == "Family") { title.AddPoints(15); }
            }
        }
        else if (userInput == "H") {
            for (Media& title : media) {
                if (title.genre == "Myrstery") { title.AddPoints(15); }
            }
        }
    }

    // More specific way to get different points for each media title. Use points, score, first char of title, and title length
    for (Media& title : media) {
        title.points = (title.points * 100000) + (title.rating * 10000) + ((255 - title.title[0]) * 10) + title.title.size();
    }

    // add print functions here to display sorting
    // author Alejandro
    // 08/04/24
    // Clone the media vector for each sort to ensure they sort the same data

    vector<Media> mediaForMergeSort = media;
    vector<Media> mediaForQuickSort = media;
    cout << "\n";

    // Measure time for Merge Sort
    cout << "Sorting with Merge Sort..." << endl;
    auto startMerge = chrono::high_resolution_clock::now();
    mergeSort(mediaForMergeSort, 0, mediaForMergeSort.size() - 1);
    auto endMerge = chrono::high_resolution_clock::now();
    auto durationMerge = chrono::duration_cast<chrono::milliseconds>(endMerge - startMerge).count();

    // Simulate progress for visualization
    for (int i = 0; i <= 100; ++i) {
        displayLoadingBar(i, 100);
        this_thread::sleep_for(chrono::milliseconds(durationMerge / 100));
    }
    cout << "\nMerge Sort Time: " << durationMerge << " ms" << endl;

    // Measure time for Quick Sort
    cout << "\nSorting with Quick Sort..." << endl;
    auto startQuick = chrono::high_resolution_clock::now();
    quickSort(mediaForQuickSort, 0, mediaForQuickSort.size() - 1);
    auto endQuick = chrono::high_resolution_clock::now();
    auto durationQuick = chrono::duration_cast<chrono::milliseconds>(endQuick - startQuick).count();

    // Simulate progress for visualization
    for (int i = 0; i <= 100; ++i) {
        displayLoadingBar(i, 100);
        this_thread::sleep_for(chrono::milliseconds(durationQuick / 100));
    }
    cout << "\nQuick Sort Time: " << durationQuick << " ms\n" << endl;

    // Display top 5 recommendations using Merge Sort results
    cout << "Top Recommendations (using Merge Sort results):" << endl;
    for (int i = 0; i < 5; i++) {
        // cout << "(DEBUG) Points: " << title.points << " | "; // DEBUG: shows points before movie on printed list
        cout << "[" << i + 1 << "] "
            << mediaForMergeSort[i].title << " (" << mediaForMergeSort[i].yearString << ") - "
            << mediaForMergeSort[i].genre << " - Rating: " << mediaForMergeSort[i].rating
            << " - Maturity: " << mediaForMergeSort[i].maturity << endl; // Added maturity rating
    }

    cout << endl;

    // Display top 5 recommendations using Quick Sort results
    cout << "Top Recommendations (using Quick Sort results):" << endl;
    for (int i = 0; i < 5; i++) {
        // cout << "(DEBUG) Points: " << title.points << " | "; // DEBUG: shows points before movie on printed list
        cout << "[" << i + 1 << "] "
            << mediaForQuickSort[i].title << " (" << mediaForQuickSort[i].yearString << ") - "
            << mediaForQuickSort[i].genre << " - Rating: " << mediaForQuickSort[i].rating
            << " - Maturity: " << mediaForQuickSort[i].maturity << endl; // Added maturity rating
    }

    return 0;
}
