#include <iostream>
#include <map>
#include <string>
#include <cctype>


// So we don't have to type "std::" everywhere...
using namespace std;


string processWord(string word);
void processText(map<string, int>& wordCounts);
void outputWordsByCount(map<string, int>& wordCounts);


int main()
{
  map<string, int> wordCounts;

  // Process the text on console-input, using the skip-list.
  processText(wordCounts);

  // Finally, output the word-list and the associated counts.
  outputWordsByCount(wordCounts);
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
 * from each word, and updating a count of words processed and updating a map of 
 * how often each word is seen.
 *
 * Parameters:
 *   wordCounts    A reference to the map in which we store the number of times
 *         each processed word is scene in the console-input.  Stores (string, int)
 *         pairs, where each string is a unique word, and the int is the number of 
 *         times the word occurs in console-input.
 *
 * Return value:
 *   None.
 *   Although we will print out the total number of words we have processed and 
 *   the total number of unique words we have seen.
 */
void processText(map<string, int>& wordCounts)
{
  string word;

  int totalCount = 0;

  // Read input until there is no more!
  while (cin >> word)
  {
    string processedWord = processWord(word);
    if (processedWord.length() == 0) {
      continue;
    }

    // update total word count and map
    totalCount++;
    ++wordCounts[processedWord];
  }

  cout << "Total words in document: " << totalCount << endl;
  cout << "Unique word: " << wordCounts.size() << endl;

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