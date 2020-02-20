#include <string>
#include <vector>
#include "Corpus.hpp"
#include "Document.hpp"
#include "Math.hpp"
#include "NewlineTokenizer.hpp"
#include "Tokenizer.hpp"
#include "WhitespaceTokenizer.hpp"

inline double corpusSimilarity(Corpus<std::string> c1, Corpus<std::string> c2) {
	double similaritySum = 0;

	std::vector<Document> a = c1.getDocuments();
	std::vector<Document> b = c2.getDocuments();

	for(int i = 0; i < a.size(); i++) {
		similaritySum += Math::dotProduct(a[i].getNormalizedVector(), b[i].getNormalizedVector());
	}

	return Math::divide(similaritySum, static_cast<double>(a.size()));
}

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
	testTokenizers.push_back(&wst);

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
		std::cout << corpus.getTokenizer()->getId() << " " << corpusSimilarity(corpus, corpusStandard) << std::endl;
	}

	return 0;
}
