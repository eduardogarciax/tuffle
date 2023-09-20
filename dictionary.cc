#include "dictionary.h"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

Dictionary::Dictionary(const std::string& valid_tuffles_filename,
                       const std::string& valid_guesses_filename) {
  // Read from the file containing all valid secret
  // tuffles, and insert them into the valid_tuffles_ vector.
  std::ifstream tuffles_file(valid_tuffles_filename);
  std::string word;
  while (tuffles_file >> word) {
    valid_tuffles_.push_back(word);
  }

  // Read from the file containing all valid guesses,
  // and insert them into the valid_guesses_ set.
  std::ifstream guesses_file(valid_guesses_filename);
  while (guesses_file >> word) {
    valid_guesses_.insert(word);
  }
  // Use the current time as a seed for the random number generator.
  srand(time(nullptr));
}

bool Dictionary::IsValidGuess(const std::string& word) const {
  //=================== YOUR CODE HERE ===================
  // TODO: Return true if the given `word` is considered
  // a valid guess. If the guess is invalid, return false.
  //======================================================
  return (valid_guesses_.find(word) != valid_guesses_.end());
}

const std::string& Dictionary::GetRandomTuffle() const {
  //=================== YOUR CODE HERE ===================
  // TODO: Select and return a random Tuffle from the
  // list of valid Tuffles stored in the valid_tuffles_
  // vector.
  // Hint: we suggest using the rand() function to
  // generate a random number.
  //======================================================
  int index = rand() % (valid_tuffles_.size());
  return valid_tuffles_[index];
}