#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory> // For smart pointers

using namespace std;

// Interface for Displayable entities
class IDisplayable {
public:
    virtual void displayInfo() const = 0;
    virtual ~IDisplayable() = default;
};

// Abstract Base Class for Entity
class Entity : public IDisplayable {
protected:
    string name;

public:
    Entity(const string& entityName) : name(entityName) {}
    virtual ~Entity() {}

    string getName() const { return name; }
    void setName(const string& entityName) { name = entityName; }
};

// Album class (Single Responsibility: Manages album-specific data)
class Album : public Entity {
private:
    string releaseDate;
    vector<string> trackList;
    double sales;

public:
    Album(const string& albumTitle, const string& albumReleaseDate)
        : Entity(albumTitle), releaseDate(albumReleaseDate), sales(0.0) {}

    void addTrack(const string& track) { trackList.push_back(track); }
    void removeTrack(const string& track) {
        trackList.erase(remove(trackList.begin(), trackList.end(), track), trackList.end());
    }

    void updateSales(double amount) { sales += amount; }
    double getSales() const { return sales; }

    void displayInfo() const override {
        cout << "Album: " << name << "\nRelease Date: " << releaseDate << "\nSales: $" << sales << endl;
    }
};

// Royalty Calculator Utility (Single Responsibility)
class RoyaltyCalculator {
public:
    static double calculateRoyalties(const vector<shared_ptr<Album>>& albums, double royaltyRate) {
        double totalRoyalties = 0.0;
        for (const auto& album : albums) {
            totalRoyalties += album->getSales() * royaltyRate;
        }
        return totalRoyalties;
    }
};

// Abstract Base Class for Artist (Open/Closed: Extendable for SoloArtists, Bands, etc.)
class Artist : public Entity {
protected:
    string genre;
    double royaltyRate;
    vector<shared_ptr<Album>> albums;

public:
    Artist(const string& artistName, const string& artistGenre, double rate)
        : Entity(artistName), genre(artistGenre), royaltyRate(rate) {}

    virtual ~Artist() {}

    void releaseAlbum(const shared_ptr<Album>& album) { albums.push_back(album); }

    double calculateRoyalties() const {
        return RoyaltyCalculator::calculateRoyalties(albums, royaltyRate);
    }

    void displayAlbums() const {
        cout << "Albums Released:\n";
        for (const auto& album : albums) {
            cout << "  - " << album->getName() << endl;
        }
    }

    void displayInfo() const override = 0; // Pure virtual function
};

// SoloArtist class (Liskov Substitution: Implements Artist-specific logic)
class SoloArtist : public Artist {
public:
    SoloArtist(const string& artistName, const string& artistGenre, double rate)
        : Artist(artistName, artistGenre, rate) {}

    void displayInfo() const override {
        cout << "Solo Artist: " << name << "\nGenre: " << genre << "\nRoyalty Rate: " << royaltyRate << endl;
        displayAlbums();
    }
};

// Band class (Liskov Substitution: Implements Artist-specific logic)
class Band : public Artist {
private:
    int memberCount;

public:
    Band(const string& bandName, const string& bandGenre, double rate, int members)
        : Artist(bandName, bandGenre, rate), memberCount(members) {}

    void displayInfo() const override {
        cout << "Band: " << name << "\nGenre: " << genre << "\nMembers: " << memberCount << "\nRoyalty Rate: " << royaltyRate << endl;
        displayAlbums();
    }
};

int main() {
    // Create albums
    auto album1 = make_shared<Album>("Rocking the World", "2024-09-01");
    auto album2 = make_shared<Album>("Pop Sensation", "2024-10-15");

    album1->addTrack("Track 1");
    album1->updateSales(5000);

    album2->addTrack("Track 2");
    album2->updateSales(8000);

    // Create artists
    auto artist1 = make_shared<SoloArtist>("John Doe", "Rock", 0.1);
    auto artist2 = make_shared<Band>("The Pop Stars", "Pop", 0.15, 5);

    // Release albums
    artist1->releaseAlbum(album1);
    artist2->releaseAlbum(album2);

    // Display information
    artist1->displayInfo();
    cout << "Royalties: $" << artist1->calculateRoyalties() << endl;

    artist2->displayInfo();
    cout << "Royalties: $" << artist2->calculateRoyalties() << endl;

    return 0;
}
