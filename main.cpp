#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Forward declaration of the Contract class
class Contract {
    // Dummy Contract class for demonstration purposes
};

// Album class definition
class Album {
private:
    string title;
    string releaseDate;
    vector<string> trackList;
    double sales;
    string status;

public:
    // Constructor
    Album(string albumTitle, string albumReleaseDate) {
        this->title = albumTitle;
        this->releaseDate = albumReleaseDate;
        this->sales = 0.0;
        this->status = "In Production";
    }

    // Method to add a track to the album
    void addTrack(string track) {
        this->trackList.push_back(track);
    }

    // Method to remove a track from the album
    void removeTrack(string track) {
        this->trackList.erase(remove(this->trackList.begin(), this->trackList.end(), track), this->trackList.end());
    }

    // Method to update the sales of the album
    void updateSales(double amount) {
        this->sales += amount;
    }

    // Method to change the status of the album
    void changeStatus(string newStatus) {
        this->status = newStatus;
    }

    // Method to get the total sales of the album
    double getSales() const {
        return this->sales;
    }

    // Method to get the current status of the album
    string getStatus() const {
        return this->status;
    }
};

// Artist class definition
class Artist {
protected:
    string name;
    string genre;
    Contract contractDetails;
    double royaltyRate;
    vector<Album*> albumList;

public:
    // Constructor
    Artist(string artistName, string artistGenre, Contract contract, double rate) {
        this->name = artistName;
        this->genre = artistGenre;
        this->contractDetails = contract;
        this->royaltyRate = rate;
    }



    // Method to sign a new contract
    void signContract(Contract newContract) {
        this->contractDetails = newContract;
    }

    // Method to release a new album
    void releaseAlbum(Album* album) {
        this->albumList.push_back(album);
    }

    // Method to calculate royalties
    double calculateRoyalties() const {
        double totalRoyalties = 0.0;
        for (const Album* album : this->albumList) {
            totalRoyalties += album->getSales() * this->royaltyRate;
        }
        return totalRoyalties;
    }

    // Getter for the artist's name
    string getName() const {
        return this->name;
    }

    // Getter for the artist's genre
    string getGenre() const {
        return this->genre;
    }
};

// Main function
int main() {
    // Dummy Contract object for demonstration purposes
    Contract contract;

    // Create a dummy artist
    Artist artist("John Doe", "Rock", contract, 0.1);  // 10% royalty rate

    // Create an album and associate it with the artist
    Album album("Rocking the World", "2024-09-01");
    album.addTrack("Track 1");
    album.addTrack("Track 2");
    album.updateSales(5000);  // $5000 sales
    album.updateSales(3000);  // Additional $3000 sales
    album.changeStatus("Released");

    // Release the album through the artist
    artist.releaseAlbum(&album);

    // Print out the artist details and royalties
    cout << "Artist: " << artist.getName() << endl;
    cout << "Genre: " << artist.getGenre() << endl;
    cout << "Total Royalties: $" << artist.calculateRoyalties() << endl;
    return 0;
}
