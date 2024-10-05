#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Linked list for reviews also a node structure
struct ReviewNode {
    string comments;
    ReviewNode* next;
};

// Linked list for rating also a node structure
struct RatingNode {
    float rating;
    RatingNode* next;
};

// Movie class
class Movie {
private:
    string title;
    RatingNode* ratingHead;
    ReviewNode* reviewHead;

public:
    // Constructor
    Movie(const string& movieTitle) : title(movieTitle), ratingHead(nullptr), reviewHead(nullptr) {}

    // Add reviews at head function
    void addReview(const string& comments, float rating) {
        // Linked list that adds to review
        ReviewNode* newReview = new ReviewNode{comments, reviewHead};
        reviewHead = newReview;

        // Linked list that adds to rating
        RatingNode* newRating = new RatingNode{rating, ratingHead};
        ratingHead = newRating;
    }

    // Function to display reviews
    void displayReviews() const {
        cout << "Movie: " << title << endl;

        if (!reviewHead) {
            cout << "No reviews available." << endl;
            return;
        }

        int count = 0;
        float totalRating = 0.0;
        ReviewNode* reviewTemp = reviewHead;
        RatingNode* ratingTemp = ratingHead;

        while (reviewTemp && ratingTemp) {
            count++;
            cout << "--> Review " << count << ": " << fixed << setprecision(1) << ratingTemp->rating << " - " << reviewTemp->comments << endl;
            totalRating += ratingTemp->rating;
            reviewTemp = reviewTemp->next;
            ratingTemp = ratingTemp->next;
        }

        cout << "--> Average Rating: " << totalRating / count << endl;
    }

    // Destructuor
    ~Movie() {
        while (reviewHead) {
            ReviewNode* temp = reviewHead;
            reviewHead = reviewHead->next;
            delete temp;
        }

        while (ratingHead) {
            RatingNode* temp = ratingHead;
            ratingHead = ratingHead->next;
            delete temp;
        }
    }
};

// Generate random rate 1-5 Function
float generateRandomRating() {
    return 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 4.0f));
}

// This function will read the comments from the file and will make them into a vector
vector<string> readCommentsFromFile(const string& filename) {
    vector<string> comments;
    ifstream file(filename);
    string comment;

    if (file.is_open()) {
        while (getline(file, comment)) {
            comments.push_back(comment);
        }
        file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
    
    return comments;
}

// Main
int main() {
    srand(static_cast<unsigned>(time(0))); // Random number generation

    // Vector of movie objects
    vector<Movie> movies;
    movies.push_back(Movie("Cinderella"));
    movies.push_back(Movie("Monster House"));

    // Read from file
    vector<string> comments = readCommentsFromFile("reviews.txt");

    // Make sure there are enough comments
    if (comments.size() < 4) {
        cout << "Not enough comments in file!" << endl;
        return 1;
    }

    // This will add a review for each movie
    for (int i = 0; i < 2; ++i) {
        float rating = generateRandomRating();
        movies[0].addReview(comments[i], rating);  // This will add the review for movie 1
    }

    for (int i = 2; i < 4; ++i) {
        float rating = generateRandomRating();
        movies[1].addReview(comments[i], rating);  // This will add the review for movie 2
    }

    // Display
    cout << "\n********* Movie Reviews ********\n";
    for (const Movie& movie : movies) {
        movie.displayReviews();
        cout << endl;
    }

    return 0; // terminate
}

