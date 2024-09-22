#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Contract {
    // Dummy Contract class for demonstration purposes
};


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

    void addTrack(string track) {
        this->trackList.push_back(track);
    }

    void removeTrack(string track) {
        this->trackList.erase(remove(this->trackList.begin(), this->trackList.end(), track), this->trackList.end());
    }

    void updateSales(double amount) {
        this->sales += amount;
    }

    void changeStatus(string newStatus) {
        this->status = newStatus;
    }

    double getSales() const {
        return this->sales;
    }

    string getStatus() const {
        return this->status;
    }
};

class Artist {
protected:
    string name;
    string genre;
    Contract contractDetails;
    double royaltyRate;
    vector<Album*> albumList;

public:
    Artist(string artistName, string artistGenre, Contract contract, double rate) {
        this->name = artistName;
        this->genre = artistGenre;
        this->contractDetails = contract;
        this->royaltyRate = rate;
    }



    void signContract(Contract newContract) {
        this->contractDetails = newContract;
    }

    void releaseAlbum(Album* album) {
        this->albumList.push_back(album);
    }

    double calculateRoyalties() const {
        double totalRoyalties = 0.0;
        for (const Album* album : this->albumList) {
            totalRoyalties += album->getSales() * this->royaltyRate;
        }
        return totalRoyalties;
    }

    string getName() const {
        return this->name;
    }

    string getGenre() const {
        return this->genre;
    }
};

int main() {
    Contract* contract = new Contract();

    Artist* artists[2] = {
        new Artist("John Doe", "Rock", contract, 0.1),
        new Artist("Jane Smith", "Pop", contract, 0.15)
    };

    Album* johnAlbums[2] = {
        new Album("Rocking the World", "2024-09-01"),
        new Album("The Next Hit", "2024-12-01")
    };
    johnAlbums[0].addTrack("Track 1");
    johnAlbums[0].addTrack("Track 2");
    johnAlbums[0].updateSales(5000);
    johnAlbums[0].changeStatus("Released");

    johnAlbums[1].addTrack("Track A");
    johnAlbums[1].addTrack("Track B");
    johnAlbums[1].updateSales(3000);
    johnAlbums[1].changeStatus("Released");

    Album* janeAlbums[2] = {
        new Album("Pop Sensation", "2024-10-15"),
        new Album("Hits Forever", "2024-11-20")
    };
    janeAlbums[0].addTrack("Pop Track 1");
    janeAlbums[0].addTrack("Pop Track 2");
    janeAlbums[0].updateSales(8000);
    janeAlbums[0].changeStatus("Released");

    janeAlbums[1].addTrack("Hit Track A");
    janeAlbums[1].addTrack("Hit Track B");
    janeAlbums[1].updateSales(6000);
    janeAlbums[1].changeStatus("Released");

    for (int i = 0; i < 2; ++i) {
        artists[0].releaseAlbum(&johnAlbums[i]);
        artists[1].releaseAlbum(&janeAlbums[i]);
    }

    for (int i = 0; i < 2; ++i) {
        cout << "Artist: " << artists[i].getName() << endl;
        cout << "Genre: " << artists[i].getGenre() << endl;
        cout << "Total Royalties: $" << artists[i].calculateRoyalties() << endl;
        cout << "----------------------------" << endl;
    }

    //cleanup dynamic memory
    for(int i =0 ; i <2; ++i){
      delete artists[i];
    }

    for(int i =0; i<2; ++i){
      delete johnAlbums[i];
      delete janeAlbums[i];
    }

    return 0;
}
