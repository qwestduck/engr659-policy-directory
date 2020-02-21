#include <iostream>
#include <string>
#include <vector>
#include "Corpus.hpp"
#include "Document.hpp"
#include "Math.hpp"
#include "NewlineTokenizer.hpp"
#include "PolicyTokenizer001.hpp"
#include "Tokenizer.hpp"
#include "WhitespaceTokenizer.hpp"

int main() {
	std::vector<Tokenizer<std::wstring>*> testTokenizers;
	std::vector<Corpus<std::string>> corpora;

	// Gold standard
	Corpus<std::string> corpusStandard;
	NewlineTokenizer<std::wstring> nlt;

	corpusStandard.loadFromCSV("../test/data/corpus-metadata.csv", "../test/data/tokenized/");
	corpusStandard.setTokenizer(&nlt);
	corpusStandard.buildIndex();
	corpusStandard.normalizeDocumentVectors();

	// Test tokenizers
	WhitespaceTokenizer<std::wstring> wst;
	PolicyTokenizer001<std::wstring> pt001;
	testTokenizers.push_back(&wst);
	testTokenizers.push_back(&pt001);

	for(auto & tokenizer : testTokenizers) {
		Corpus<std::string> corpus;
		corpus.loadFromCSV("../test/data/corpus-metadata.csv", "../data/text/");
		corpus.setTokenizer(tokenizer);
		corpus.buildIndex();
		corpus.setDictionary(corpusStandard.getDictionary());
		corpus.normalizeDocumentVectors();

		corpora.push_back(corpus);
	}

	for(auto const & corpus : corpora) {
		std::cout << corpus.getTokenizer()->getId() << " " << corpus.similarityBetween(corpusStandard) << std::endl;

		if(corpus.getTokenizer()->getId() == "PolicyTokenizer001") {
			Corpus<std::string> c = corpus;
			c.printSummary();
		}
	}

	return 0;
}
