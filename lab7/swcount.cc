#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cctype>

// So we don't have to type "std::" everywhere...
using namespace std;


void initSkipList(set<string>& skipList);
string processWord(string word);
void processText(set<string>& skipList, map<string, int>& wordCounts);
void outputWordsByCount(map<string, int>& wordCounts);


int main()
{
  set<string> skipList;
  map<string, int> wordCounts;

  // Initialize the skip-list.
  initSkipList(skipList);

  // Process the text on console-input, using the skip-list.
  processText(skipList, wordCounts);

  // Finally, output the word-list and the associated counts.
  outputWordsByCount(wordCounts);
}


/*
 * This function initializes the skip-list of words.
 *
 * skipList = the set of words to skip
 */
void initSkipList(set<string>& skipList)
{
  // Use a pre-specified skip-list.

  const char *swords[] = {
    "a", "all", "am", "an", "and", "are", "as", "at",
    "be", "been", "but", "by",
    "did", "do",
    "for", "from",
    "had", "has", "have", "he", "her", "hers", "him", "his",
    "i", "if", "in", "into", "is", "it", "its",
    "me", "my",
    "not",
    "of", "on", "or",
    "so",
    "that", "the", "their", "them", "they", "this", "to",
    "up", "us",
    "was", "we", "what", "who", "why", "will", "with",
    "you", "your",
    0
  };

  for (int i = 0; swords[i] != 0; i++)
    skipList.insert(string(swords[i]));
}


/*
 * This helper-function converts a word to all lower-case, and then removes
 * any leading and/or trailing punctuation.
 *
 * Parameters:
 *   word    The word to process.  It is passed by-value so that it can be
 *           manipulated within the function without affecting the caller.
 *
 * Return value:
 *   The word after all leading and trailing punctuation have been removed.
 *   Of course, if the word is entirely punctuation (e.g. "--") then the result
 *   may be an empty string object (containing "").
 */
string processWord(string word)
{
  // convert all characters to lowercase.
  for (unsigned int k = 0; k < word.length(); k++) {
    word[k] = tolower(word[k]);
  }

  // now, strip off leading/trailing punctionation

  unsigned int i = 0;       // find the first non punct character
  while (i < word.length()) {
    if (!ispunct(word[i])) {
      break;
    }
    i++;
  }

  unsigned int j = word.length() - 1; // find the last non punct character
  while (j > 0) {
    if (!ispunct(word[j])) {
      break;
    }
    j--;
  }

  return word.substr(i, j - i + 1);  // return substring between
}

/*
 * This helper-function processes the text on console-input by reading each word 
 * until the end of the file, removing all leading and trailing punctionuation 
 * from each word, skipping over any words that are in the skip list, and updating
 * a map of how often each word is seen.
 *
 * Parameters:
 *   skipList      A set of strings that should be skipped over, and not included
 *         in the map of words that we are keeping track of.
 *   wordCounts    A reference to the map in which we store the number of times
 *         each processed word is scene in the console-input.  Stores (string, int)
 *         pairs, where each string is a unique word, and the int is the number of 
 *         times the word occurs in console-input.
 *
 * Return value:
 *   None.
 *   Although we will print out the total number of words we have processed and 
 *   the total number of unique words we have seen, as well as the total number
 *   of words we have skipped over because they were in the skip list.
 */
void processText(set<string>& skipList, map<string, int>& wordCounts)
{
  string word;

  int totalCount = 0;
  int skippedWords = 0;

  // Read input until there is no more!
  while (cin >> word)
  {
    string processedWord = processWord(word);
    if (processedWord.length() == 0) {
      continue;
    }

    // update total word count 
    totalCount++;

    // if the word is in the skipped word list, update the skipped words 
    // counter and go to next word.
    if (skipList.find(processedWord) != skipList.end())
    {
      skippedWords++;
      continue;
    }

    ++wordCounts[processedWord];  // update map
  }

  cout << "Total words in document: " << totalCount << endl;
  cout << "Unique words: " << wordCounts.size() << endl;
  cout << "Skipped " << skippedWords << " words." << endl;
}


/*
 * This helper-function outputs the generated word-list in descending order
 * of count.  The function uses an STL associative container to sort the words
 * by how many times they appear.  Because multiple words can have the same
 * counts, a multimap is used.
 */
void outputWordsByCount(map<string, int>& wordCounts)
{
  multimap<int, string, greater<int> > sortByCount;
  map<string, int>::const_iterator wIter;

  for (wIter = wordCounts.begin(); wIter != wordCounts.end(); wIter++)
    sortByCount.insert(pair<int, string>(wIter->second, wIter->first));

  multimap<int, string>::const_iterator cIter;
  for (cIter = sortByCount.begin(); cIter != sortByCount.end(); cIter++)
    cout << cIter->second << "\t" << cIter->first << endl;
}