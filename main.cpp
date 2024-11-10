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

    static int totalAlbumsReleased;

public:
    // Constructor
    Album(string albumTitle, string albumReleaseDate) {
        setTitle(albumTitle);
        setReleaseDate(albumReleaseDate);
        setSales(0.0);
        setStatus("In Production");
        totalAlbumsReleased++;
    }

    ~Album(){
        totalAlbumsReleased--;
    }

    // Accessors and mutators
    string getTitle() const { return title; }
    void setTitle(const string& albumTitle) { title = albumTitle; }

    string getReleaseDate() const { return releaseDate; }
    void setReleaseDate(const string& albumReleaseDate) { releaseDate = albumReleaseDate; }

    double getSales() const { return sales; }
    void setSales(double albumSales) { sales = albumSales; }

    string getStatus() const { return status; }
    void setStatus(const string& albumStatus) { status = albumStatus; }

    void addTrack(const string& track) {
        trackList.push_back(track);
    }

    void removeTrack(const string& track) {
        trackList.erase(remove(trackList.begin(), trackList.end(), track), trackList.end());
    }

    void updateSales(double amount) {
        setSales(getSales() + amount);  // Use mutator
    }

    void changeStatus(const string& newStatus) {
        setStatus(newStatus);  // Use mutator
    }

    static int getTotalAlbumsReleased(){
        return totalAlbumsReleased;
    }

};

int Album::totalAlbumsReleased = 0;

class Artist {
protected:
    string name;
    string genre;
    Contract contractDetails;
    double royaltyRate;
    vector<Album*> albumList;

    static double totalRoyaltiesAccumulated;

public:
    Artist(const string& artistName, const string& artistGenre, Contract contract, double rate) {
        setName(artistName);
        setGenre(artistGenre);
        signContract(contract);
        setRoyaltyRate(rate);
    }

    ~Artist(){} //destructor

    // Accessors and mutators
    string getName() const { return name; }
    void setName(const string& artistName) { name = artistName; }

    string getGenre() const { return genre; }
    void setGenre(const string& artistGenre) { genre = artistGenre; }

    double getRoyaltyRate() const { return royaltyRate; }
    void setRoyaltyRate(double rate) { royaltyRate = rate; }

    void signContract(const Contract& newContract) {
        contractDetails = newContract;
    }

    void releaseAlbum(Album* album) {
        albumList.push_back(album);
    }

    double calculateRoyalties() const {
        double totalRoyalties = 0.0;
        for (const Album* album : albumList) {
            totalRoyalties += album->getSales() * getRoyaltyRate();  // Use accessor
        }
        return totalRoyalties;
    }

    void accumulateRoyalties(){
        double artistRoyalties = calculateRoyalties();
        totalRoyaltiesAccumulated += artistRoyalties;
    }

    static double getTotalRoyaltiesAccumulated(){
        return totalRoyaltiesAccumulated;
    }
};

double Artist::totalRoyaltiesAccumulated = 0.0;

int main() {
    Contract* contract = new Contract();

    Artist* artists[2] = {
        new Artist("John Doe", "Rock", *contract, 0.1),
        new Artist("Jane Smith", "Pop", *contract, 0.15)
    };

    Album* johnAlbums[2] = {
        new Album("Rocking the World", "2024-09-01"),
        new Album("The Next Hit", "2024-12-01")
    };
    johnAlbums[0]->addTrack("Track 1");
    johnAlbums[0]->addTrack("Track 2");
    johnAlbums[0]->updateSales(5000);
    johnAlbums[0]->changeStatus("Released");

    johnAlbums[1]->addTrack("Track A");
    johnAlbums[1]->addTrack("Track B");
    johnAlbums[1]->updateSales(3000);
    johnAlbums[1]->changeStatus("Released");

    Album* janeAlbums[2] = {
        new Album("Pop Sensation", "2024-10-15"),
        new Album("Hits Forever", "2024-11-20")
    };
    janeAlbums[0]->addTrack("Pop Track 1");
    janeAlbums[0]->addTrack("Pop Track 2");
    janeAlbums[0]->updateSales(8000);
    janeAlbums[0]->changeStatus("Released");

    janeAlbums[1]->addTrack("Hit Track A");
    janeAlbums[1]->addTrack("Hit Track B");
    janeAlbums[1]->updateSales(6000);
    janeAlbums[1]->changeStatus("Released");

    for (int i = 0; i < 2; ++i) {
        artists[0]->releaseAlbum(johnAlbums[i]);
        artists[1]->releaseAlbum(janeAlbums[i]);
    }

    for (int i = 0; i < 2; ++i) {
        artists[i]->accumulateRoyalties();
        cout << "Artist: " << artists[i]->getName() << endl;
        cout << "Genre: " << artists[i]->getGenre() << endl;
        cout << "Total Royalties: $" << artists[i]->calculateRoyalties() << endl;
        cout << "----------------------------" << endl;
    }

    cout << "Total Albums Released: " << Album::getTotalAlbumsReleased() << endl;
    cout << "Total Royalties Accumulated by All Artists: $" << Artist::getTotalRoyaltiesAccumulated() << endl;

    // Cleanup dynamic memory
    for (int i = 0; i < 2; ++i) {
        delete artists[i];
        delete johnAlbums[i];
        delete janeAlbums[i];
    }

    delete contract;

    return 0;
}
