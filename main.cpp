#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Abstract Base Class
class Entity {
protected:
    string name;

public:
    Entity(const string& entityName) : name(entityName) {}
    virtual ~Entity() {}

    // Pure virtual function for displaying information
    virtual void displayInfo() const = 0;

    string getName() const { return name; }
    void setName(const string& entityName) { name = entityName; }
};

// Derived Class from Entity: Album
class Album : public Entity {
private:
    string releaseDate;
    vector<string> trackList;
    double sales;
    string status;

    static int totalAlbumsReleased;

public:
    Album(const string& albumTitle, const string& albumReleaseDate)
        : Entity(albumTitle), releaseDate(albumReleaseDate), sales(0.0), status("In Production") {
        totalAlbumsReleased++;
    }

    ~Album() { totalAlbumsReleased--; }

    void addTrack(const string& track) { trackList.push_back(track); }
    void removeTrack(const string& track) {
        trackList.erase(remove(trackList.begin(), trackList.end(), track), trackList.end());
    }

    void updateSales(double amount) { sales += amount; }
    void changeStatus(const string& newStatus) { status = newStatus; }

    double getSales() const { return sales; }

    static int getTotalAlbumsReleased() { return totalAlbumsReleased; }

    // Overriding virtual function
    void displayInfo() const override {
        cout << "Album: " << name << "\nRelease Date: " << releaseDate << "\nStatus: " << status << "\nSales: $" << sales << endl;
    }
};

int Album::totalAlbumsReleased = 0;

// Derived Class from Entity: Artist
class Artist : public Entity {
protected:
    string genre;
    double royaltyRate;
    vector<Album*> albumList;

    static double totalRoyaltiesAccumulated;

public:
    Artist(const string& artistName, const string& artistGenre, double rate)
        : Entity(artistName), genre(artistGenre), royaltyRate(rate) {}

    virtual ~Artist() {}

    void releaseAlbum(Album* album) { albumList.push_back(album); }

    double calculateRoyalties() const {
        double totalRoyalties = 0.0;
        for (const Album* album : albumList) {
            totalRoyalties += album->getSales() * royaltyRate;
        }
        return totalRoyalties;
    }

    void accumulateRoyalties() {
        double artistRoyalties = calculateRoyalties();
        totalRoyaltiesAccumulated += artistRoyalties;
    }

    static double getTotalRoyaltiesAccumulated() { return totalRoyaltiesAccumulated; }

    // Overriding virtual function
    void displayInfo() const override {
        cout << "Artist: " << name << "\nGenre: " << genre << "\nRoyalty Rate: " << royaltyRate << endl;
        cout << "Albums Released:\n";
        for (const Album* album : albumList) {
            cout << "  - " << album->getName() << endl;
        }
    }
};

double Artist::totalRoyaltiesAccumulated = 0.0;

// Derived Class from Artist: SoloArtist
class SoloArtist : public Artist {
public:
    SoloArtist(const string& artistName, const string& artistGenre, double rate)
        : Artist(artistName, artistGenre, rate) {}

    void displayInfo() const override {
        cout << "Solo Artist: " << name << "\nGenre: " << genre << "\nRoyalty Rate: " << royaltyRate << endl;
        cout << "Albums:\n";
        for (const Album* album : albumList) {
            cout << "  - " << album->getName() << endl;
        }
    }
};

// Derived Class from Artist: Band
class Band : public Artist {
private:
    int memberCount;

public:
    Band(const string& bandName, const string& bandGenre, double rate, int members)
        : Artist(bandName, bandGenre, rate), memberCount(members) {}

    void displayInfo() const override {
        cout << "Band: " << name << "\nGenre: " << genre << "\nMembers: " << memberCount << "\nRoyalty Rate: " << royaltyRate << endl;
        cout << "Albums:\n";
        for (const Album* album : albumList) {
            cout << "  - " << album->getName() << endl;
        }
    }
};

int main() {
    // Create albums
    Album* album1 = new Album("Rocking the World", "2024-09-01");
    Album* album2 = new Album("Pop Sensation", "2024-10-15");

    album1->addTrack("Track 1");
    album1->updateSales(5000);
    album1->changeStatus("Released");

    album2->addTrack("Track 2");
    album2->updateSales(8000);
    album2->changeStatus("Released");

    // Create artists
    SoloArtist* artist1 = new SoloArtist("John Doe", "Rock", 0.1);
    Band* artist2 = new Band("The Pop Stars", "Pop", 0.15, 5);

    // Release albums
    artist1->releaseAlbum(album1);
    artist2->releaseAlbum(album2);

    // Display information
    artist1->displayInfo();
    cout << "Royalties: $" << artist1->calculateRoyalties() << endl;

    artist2->displayInfo();
    cout << "Royalties: $" << artist2->calculateRoyalties() << endl;

    cout << "Total Albums Released: " << Album::getTotalAlbumsReleased() << endl;
    cout << "Total Royalties Accumulated: $" << Artist::getTotalRoyaltiesAccumulated() << endl;

    // Clean up memory
    delete album1;
    delete album2;
    delete artist1;
    delete artist2;

    return 0;
}
