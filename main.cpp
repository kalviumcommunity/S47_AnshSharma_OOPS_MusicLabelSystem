#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Album {
private:
  string title;
  string releaseDate;
  vector<std::string> trackList;
  double sales;
  string status;

public:
  Album(string title, string releaseDate) {
    title = title;
    releaseDate = releaseDate;
    sales = 0.0;
    status = "In Production";
  }

  void addTrack(string track) { trackList.push_back(track); }

  void removeTrack(string track) {
      trackList.erase(remove(trackList.begin(),trackList.end(), track), trackList.end();
  }

  void updateSales(double amount) { sales += amount; }

  void changeStatus(string newStatus) { status = newStatus; }

  double getSales() { return sales; }

  string getStatus() { return status; }
};

int main() {
  Album album("My First Album", "2024-09-01");
  album.addTrack("Track 1");
  album.addTrack("Track 2");
  album.updateSales(1000);
  album.changeStatus("Released");

  cout << "Album: " << album.getStatus()
            << " with Sales: " << album.getSales() << std::endl;

  return 0;
}

