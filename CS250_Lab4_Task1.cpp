#include <iostream>
#include <string>
using namespace std;

struct Song {
    int id;
    string name;
    string duration;

    Song* prev;
    Song* next;

    Song(int i, string n, string d) {
        id = i;
        name = n;
        duration = d;

        prev = nullptr;
        next = nullptr;
    }
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:

    Playlist() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~Playlist() {
        Song* temp = head;

        while (temp != nullptr) {
            Song* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }

    // Add a new song at the end
    void addSong(int id, string name, string duration) {

        Song* newSong = new Song(id, name, duration);

        if (head == nullptr) {
            head = newSong;
            tail = newSong;
            current = newSong;
        }
        else {
            newSong->prev = tail;
            tail->next = newSong;
            tail = newSong;
        }

        cout << "Song added successfully.\n";
    }

    // Delete a song using its ID
    void deleteSong(int id) {

        Song* temp = head;

        while (temp != nullptr && temp->id != id) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Song not found.\n";
            return;
        }

        // If deleting the first node
        if (temp->prev == nullptr) {
            head = temp->next;
        }
        else {
            temp->prev->next = temp->next;
        }

        // If deleting the last node
        if (temp->next == nullptr) {
            tail = temp->prev;
        }
        else {
            temp->next->prev = temp->prev;
        }

        // Update current song if necessary
        if (current == temp) {

            if (temp->next != nullptr) {
                current = temp->next;
            }
            else {
                current = temp->prev;
            }
        }

        delete temp;

        if (head == nullptr) {
            current = nullptr;
        }

        cout << "Song deleted successfully.\n";
    }

    // Display from first to last
    void displayForward() {

        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;

        cout << "\n===== PLAYLIST FORWARD =====\n";

        while (temp != nullptr) {

            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Duration: " << temp->duration
                 << endl;

            temp = temp->next;
        }
    }

    // Display from last to first
    void displayBackward() {

        if (tail == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = tail;

        cout << "\n===== PLAYLIST BACKWARD =====\n";

        while (temp != nullptr) {

            cout << "ID: " << temp->id
                 << " | Name: " << temp->name
                 << " | Duration: " << temp->duration
                 << endl;

            temp = temp->prev;
        }
    }

    // Search song using ID
    void searchSong(int id) {

        Song* temp = head;

        while (temp != nullptr) {

            if (temp->id == id) {

                cout << "\n===== SONG FOUND =====\n";

                cout << "ID: " << temp->id << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Duration: " << temp->duration << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "Song not found.\n";
    }

    // Move to next song
    void playNext() {

        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->next != nullptr) {

            current = current->next;

            cout << "Now Playing: "
                 << current->name << endl;
        }
        else {
            cout << "Already at the last song.\n";
        }
    }

    // Move to previous song
    void playPrevious() {

        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->prev != nullptr) {

            current = current->prev;

            cout << "Now Playing: "
                 << current->name << endl;
        }
        else {
            cout << "Already at the first song.\n";
        }
    }

    // Reverse the DLL
    void reversePlaylist() {

        Song* temp = head;

        while (temp != nullptr) {

            Song* nextNode = temp->next;

            temp->next = temp->prev;
            temp->prev = nextNode;

            temp = nextNode;
        }

        Song* swapNode = head;

        head = tail;
        tail = swapNode;

        cout << "Playlist reversed successfully.\n";
    }
};

int main() {

    Playlist playlist;

    int choice;

    do {

        cout << "\n========== PLAYLIST MENU ==========\n";

        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {

            int id;
            string name;
            string duration;

            cout << "Enter Song ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Song Name: ";
            getline(cin, name);

            cout << "Enter Duration (minutes:seconds): ";
            cin >> duration;

            playlist.addSong(id, name, duration);
        }

        else if (choice == 2) {

            int id;

            cout << "Enter Song ID to delete: ";
            cin >> id;

            playlist.deleteSong(id);
        }

        else if (choice == 3) {

            playlist.displayForward();
        }

        else if (choice == 4) {

            playlist.displayBackward();
        }

        else if (choice == 5) {

            int id;

            cout << "Enter Song ID to search: ";
            cin >> id;

            playlist.searchSong(id);
        }

        else if (choice == 6) {

            playlist.playNext();
        }

        else if (choice == 7) {

            playlist.playPrevious();
        }

        else if (choice == 8) {

            playlist.reversePlaylist();
        }

        else if (choice == 9) {

            cout << "Exiting...\n";
        }

        else {

            cout << "Invalid choice.\n";
        }

    } while (choice != 9);

    return 0;
}