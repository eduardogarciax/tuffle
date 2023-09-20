#include "tuffle.h"

#include <algorithm>

#include "gamestate.h"

// ========================= YOUR CODE HERE =========================
// This implementation file is where you should implement the member
// functions declared in the header, only if you didn't implement
// them inline in the header.
//
// Remember to specify the name of the class with :: in this format:
//     <return type> MyClassName::MyFunction() {
//        ...
//     }
// to tell the compiler that each function belongs to the TuffleGame class.
// ===================================================================
std::string GetcorrectAnswer(std::string guess, std::string answer) {
  std::string color = "BBBBB";
  for (int i = 0; i < answer.size(); i++) {
    if (guess[i] == answer[i]) {
      color[i] = 'G';
      answer[i] = '!';
    }
  }
  for (int i = 0; i < answer.size(); i++) {
    if (answer.find(guess.at(i)) != std::string::npos) {
      int index = answer.find(guess[i]);
      if (color[i] != 'G') {
        color.at(i) = 'Y';
        answer.at(index) = '!';
      }
    }
  }
  return color;
}
void TuffleGame::NewGame() {
  game_state_ = GameState(dictionary_.GetRandomTuffle());
  game_state_.SetStatus("active");
}
void TuffleGame::LetterKeyPressed(char key) {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  game_state_.SetError("");

  std::vector<std::string> guesses = game_state_.GetGuesses();

  if (guesses.size() == 0) {
    guesses.push_back("");
  }
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  if (guess.size() != 5) {
    guesses.at(index) = guess + key;

    game_state_.SetGuess(guesses);
  }
}
void TuffleGame::EnterKeyPressed() {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  std::vector<std::string> guesses = game_state_.GetGuesses();
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  bool valid = dictionary_.IsValidGuess(guess);
  if (not valid) {
    game_state_.SetError("Invalid guess.");
    return;
  }

  std::string correct_color = GetcorrectAnswer(guess, game_state_.GetAnswer());
  std::vector<std::string> vector_color = game_state_.GetBoardColors();
  vector_color.push_back(correct_color);
  game_state_.SetBoardColors(vector_color);

  if (correct_color == "GGGGG") {
    game_state_.SetStatus("win");
  } else if (guesses.size() > 5) {
    game_state_.SetStatus("lose");
  } else {
    guesses.push_back("");
    game_state_.SetGuess(guesses);
  }
}

void TuffleGame::DeleteKeyPressed() {
  if (game_state_.GetStatus() != "active") {
    return;
  }
  game_state_.SetError("");
  std::vector<std::string> guesses = game_state_.GetGuesses();
  int index = guesses.size() - 1;
  std::string guess = guesses.at(index);
  if (guess == "") {
    return;
  }
  guess.pop_back();
  guesses.at(index) = guess;
  game_state_.SetGuess(guesses);
}

crow::json::wvalue TuffleGame::GameStateInJson() {
  // The JSON object to return to the Tuffle Frontend.
  crow::json::wvalue game_state_json({});

  // ===================== YOUR CODE HERE =====================
  // Fill the game_state_json with the data expected by the
  // Tuffle frontend. The frontend expects the following keys:
  //   1. "answer"
  //   2. "boardColors"
  //   3. "guessedWords"
  //   4. "gameStatus"
  //   5. "errorMessage"
  //   6. [OPTIONAL] "letterColors"
  // See the "JSON Response" section of tinyurl.com/cpsc121-f22-tuffle
  //
  // You can set the key in the JSON to a value like so:
  //             game_state_json[<key>] = <value>
  //
  // See below for an example to set the "answer" key:
  game_state_json["answer"] = game_state_.GetAnswer();
  game_state_json["boardColors"] = game_state_.GetBoardColors();
  game_state_json["guessedWords"] = game_state_.GetGuesses();
  game_state_json["gameStatus"] = game_state_.GetStatus();
  game_state_json["errorMessage"] = game_state_.GetError();
  // you have to put these
  // ==========================================================
  return game_state_json;
}