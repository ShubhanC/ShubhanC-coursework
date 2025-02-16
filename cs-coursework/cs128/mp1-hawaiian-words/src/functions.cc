#include "functions.hpp"

#include <iostream>
#include <map>
#include <stdexcept>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  std::cout << "Input to StringToLower() : " << word << std::endl;
  std::string lowercase_word = word;
  for (unsigned int i = 0; i < word.size(); i++) {
    if ((IsVowel(word[i])) || (IsConsonant(word[i]))) {
      lowercase_word[i] = tolower(word[i]);
    } else {
      lowercase_word[i] = word[i];
    }
  }
  return lowercase_word;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  std::cout << "Input to IsVowelGroup() : \"" << v1 << "\" \"" << v2 << "\""
            << std::endl;
  if ((IsVowel(v1)) && (IsVowel(v2))) {
    if (v1 == 'a') {
      return (((v2 == 'e') || (v2 == 'i') || (v2 == 'o') || (v2 == 'u')));
    }
    if (v1 == 'e') {
      return ((v2 == 'i') || (v2 == 'u'));
    }
    if (v1 == 'i') {
      return (v2 == 'u');
    }
    if (v1 == 'o') {
      return ((v2 == 'i') || (v2 == 'u'));
    }
    if (v1 == 'u') {
      return (v2 == 'i');
    }
    return false;
  }
  return false;
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  std::cout << "Input to IsVowel() : \"" << v << "\"" << std::endl;
  char v_lowercase = tolower(v);
  return ((v_lowercase == 'a') || (v_lowercase == 'e') ||
          (v_lowercase == 'i') || (v_lowercase == 'o') || (v_lowercase == 'u'));
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  std::cout << "Input to IsConsonant() : \"" << c << "\"" << std::endl;
  char c_lowercase = tolower(c);
  return ((c_lowercase == 'p') || (c_lowercase == 'k') ||
          (c_lowercase == 'h') || (c_lowercase == 'l') ||
          (c_lowercase == 'm') || (c_lowercase == 'n') || (c_lowercase == 'w'));
}

/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  std::cout << "Input to IsValidCharacter() : \"" << c << "\"" << std::endl;
  char char_lowercase = tolower(c);
  if (IsVowel(char_lowercase)) {
    return true;
  }
  if (IsConsonant(char_lowercase)) {
    return true;
  }
  if ((c == ' ') || (c == '\'')) {
    return true;
  }
  return false;
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  std::cout << "Input to IsValidWord() : " << word << std::endl;
  unsigned int count = 0;
  for (unsigned int i = 0; i < word.size(); i++) {
    if (IsValidCharacter(word[i])) {
      count++;
    }
  }
  return (count == word.size());
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a char
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  std::cout << "Input to ConsonantPronunciation() : \"" << c << "\" \"" << prev
            << "\"" << std::endl;
  if (((prev == 'i') || (prev == 'e')) && (c == 'w')) {
    return 'v';
  }
  return c;
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  std::cout << "Input to VowelGroupPronunciation() : \"" << v1 << "\" \"" << v2
            << "\"" << std::endl;
  std::map<std::string, std::string> vowel_group;
  std::string vowel_group_input;
  vowel_group_input += v1;
  vowel_group_input += v2;
  vowel_group["ae"] = "eye";
  vowel_group["ai"] = "eye";
  vowel_group["ao"] = "ow";
  vowel_group["au"] = "ow";
  vowel_group["ei"] = "ay";
  vowel_group["eu"] = "eh-oo";
  vowel_group["iu"] = "ew";
  vowel_group["oi"] = "oy";
  vowel_group["ou"] = "ow";
  vowel_group["ui"] = "ooey";
  return vowel_group[vowel_group_input];
}

/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  std::cout << "Input to SingleVowelPronunciation() : \"" << v << "\""
            << std::endl;
  std::string single_vowel_pronounciation;
  if (v == 'a') {
    single_vowel_pronounciation = "ah";
  } else if (v == 'e') {
    single_vowel_pronounciation = "eh";
  } else if (v == 'i') {
    single_vowel_pronounciation = "ee";
  } else if (v == 'o') {
    single_vowel_pronounciation = "oh";
  } else if (v == 'u') {
    single_vowel_pronounciation = "oo";
  }
  return single_vowel_pronounciation;
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  std::cout << "Input to ProcessCharacter() : \"" << prev << "\" \"" << curr
            << "\" \"" << next << "\"" << std::endl;
  std::string pronounciation;
  if (IsVowel(curr)) {
    if (IsVowelGroup(curr, next)) {
      pronounciation = VowelGroupPronunciation(curr, next);
    } else {
      pronounciation = SingleVowelPronunciation(curr);
    }
  } else if (IsConsonant(curr)) {
    pronounciation += ConsonantPronunciation(curr, prev);
  } else {
    pronounciation += curr;
  }
  return pronounciation;
}

std::string ProcessCharacterZero(const char& curr, const char& next) {
  std::cout << "Input to ProcessCharacter() : \"" << curr << "\" \"" << next
            << "\"" << std::endl;
  std::string pronounciation;
  if (IsVowel(curr)) {
    if (IsVowelGroup(curr, next)) {
      pronounciation = VowelGroupPronunciation(curr, next);
    } else {
      pronounciation = SingleVowelPronunciation(curr);
    }
  } else {
    pronounciation += curr;
  }
  return pronounciation;
}

std::string ProcessCharacterEnd(const char& prev, const char& curr) {
  std::cout << "Input to ProcessCharacter() : \"" << prev << "\" \"" << curr
            << "\"" << std::endl;
  std::string pronounciation;
  if (IsVowel(curr)) {
    pronounciation = SingleVowelPronunciation(curr);
  } else if (IsConsonant(curr)) {
    pronounciation += ConsonantPronunciation(curr, prev);
  } else {
    pronounciation += curr;
  }
  return pronounciation;
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  std::cout << "Input to Pronunciation() : " << word << std::endl;
  char apostrophe = '\'';
  std::string pronounciation;
  for (unsigned int i = 0; i < word.size(); i++) {
    if (i == 0) {
      pronounciation += ProcessCharacterZero(word[i], word[i + 1]);
    } else if ((i > 0) && (i < word.size() - 1)) {
      pronounciation += ProcessCharacter(word[i - 1], word[i], word[i + 1]);
    } else if (i == word.size() - 1) {
      pronounciation += ProcessCharacterEnd(word[i - 1], word[i]);
    }
    if ((IsVowel(word[i])) && (i < word.size() - 1)) {
      if (IsVowelGroup(word[i], word[i + 1])) {
        i++;
      }
      if (((word[i + 1] != ' ') && (word[i + 1] != apostrophe)) &&
          (i < word.size() - 1)) {
        pronounciation += '-';
      }
    }
  }
  return pronounciation;
}

/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
  std::cout << "Input to GetPronunciation() : " << hawaiian_word << std::endl;
  std::string convert = StringToLower(hawaiian_word);
  std::string pronouncation;
  if (IsValidWord(convert)) {
    pronouncation = Pronunciation(convert);
  } else {
    throw std::invalid_argument("Inputted string contains invalid characters");
  }
  return pronouncation;
}