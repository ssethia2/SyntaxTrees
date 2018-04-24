#include <freeling.h>
#include <iostream>

freeling::maco_options my_maco_options(const wstring &lang, const wstring &path) {
	// create options pack
	freeling::maco_options opt(lang);
	// fill it with files for morphological submodules. Only those that are going
	// to be used need to be provided.
	opt.UserMapFile = L"";
	opt.LocutionsFile = path + L"locucions.dat";
	opt.AffixFile = path + L"afixos.dat";
	opt.ProbabilityFile = path + L"probabilitats.dat";
	opt.DictionaryFile = path + L"dicc.src";
	opt.NPdataFile = path + L"np.dat";
	opt.PunctuationFile = path + L"../common/punct.dat";

	return opt;
}

void ProcessSentences(const list<freeling::sentence> &ls) {

	// for each sentence in list
	for (list<freeling::sentence>::const_iterator is = ls.begin(); is != ls.end(); ++is) {

		// for each word in sentence
		for (freeling::sentence::const_iterator w = is->begin(); w != is->end(); ++w) {

			// print word form, with PoS and lemma chosen by the tagger
			wcout << L"word '" << w->get_form() << L"'" << endl;
			// print possible analysis in word, output lemma, tag and probability
			wcout << L"  Possible analysis: {";
			for (freeling::word::const_iterator a = w->analysis_begin(); a != w->analysis_end(); ++a)
				wcout << L" (" << a->get_lemma() << L"," << a->get_tag() << L")";
			wcout << L" }" << endl;
			wcout << L"  Selected analysis: (" << w->get_lemma() << L", " << w->get_tag() << L")" << endl;
		}

		// sentence separator
		wcout << endl;
	}
}

int main() {
	// set locale to an UTF8 compatible locale
	freeling::util::init_locale(L"default");

	// Use 'English' as default language
	wstring lang = L"en";
	// Use /usr/local as installation path
	wstring ipath = L"/usr/local";

	// path to language data
	wstring lpath = ipath + L"/share/freeling/" + lang + L"/";

	// create analyzers
	freeling::tokenizer tk(lpath + L"tokenizer.dat");
	freeling::splitter sp(lpath + L"splitter.dat");

	// create morphological analyzer with desired options
	freeling::maco morfo(my_maco_options(lang, lpath));
	// activate/deactivate desired morphological submodules
	morfo.set_active_options(false,// UserMap
		true, // NumbersDetection,
		true, //  PunctuationDetection,
		true, //  DatesDetection,
		true, //  DictionarySearch,
		true, //  AffixAnalysis,
		false, //  CompoundAnalysis,
		true, //  RetokContractions,
		true, //  MultiwordsDetection,
		true, //  NERecognition,
		false, //  QuantitiesDetection,
		true);  //  ProbabilityAssignment

				// create a hmm tagger
	freeling::hmm_tagger tagger(lpath + L"tagger.dat", true, FORCE_TAGGER);

	// get all input text in a single string, keeping line breaks
	wstring text = L"Hi, please tag these words";

	// tokenize input line into a list of words
	list<freeling::word> lw = tk.tokenize(text);
	// split list of words into sentences.
	list<freeling::sentence> ls = sp.split(lw);
	// perform morphosyntactic analysis and disambiguation
	morfo.analyze(ls);
	tagger.analyze(ls);

	// do whatever is needed with processed sentences
	ProcessSentences(ls);
}