#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

namespace DynamicStrategy {
	/// <summary>
	/// Markdown outputs lists like:
	///		* list item 1
	///		* list item 2
	///		...
	/// 
	/// Html outputs lists like:
	///		<ul>
	///			<li> item 1 </li>
	///			<li> item 2 </li>
	///		</ul>
	/// </summary>
	enum class OutputFormat {
		markdown,
		html
	};

	struct ListStrategy {
		virtual void Start(ostringstream& oss) {}
		virtual void AddListItem(ostringstream& oss, const string& item) = 0;
		virtual void End(ostringstream& oss) {}
	};

	struct MarkdownListStrategy : ListStrategy {
		void AddListItem(ostringstream& oss, const string& item) override {
			oss << "* " << item << endl;
		}
	};

	struct HtmlListStrategy : ListStrategy {
		void Start(ostringstream& oss) override{
			oss << "<ul>" << endl;
		}
		void AddListItem(ostringstream& oss, const string& item) override{
			oss << "<li>" << item << "</li>" << endl;
		}
		void End(ostringstream& oss) override{
			oss << "</ul>" << endl;
		}
	};

	struct TextProcessor {
		void Clear() {
			m_oss.str("");
			m_oss.clear();
		}

		void AppendList(const vector<string>& items) {
			m_listStrategy->Start(m_oss);
			for (auto&& item : items) {
				m_listStrategy->AddListItem(m_oss, item);
			}

			m_listStrategy->End(m_oss);
		}

		void SetOutputFormat(const OutputFormat& format) {
			switch (format) {
			case OutputFormat::markdown:
				m_listStrategy = make_unique<MarkdownListStrategy>();
				break;
			case OutputFormat::html:
				m_listStrategy = make_unique<HtmlListStrategy>();
				break;
			}
		}

		string str() const { return m_oss.str(); }

	private:
		ostringstream m_oss;
		unique_ptr<ListStrategy> m_listStrategy;
	};
}

void DynamicStrategyExample() {
	using namespace DynamicStrategy;

	TextProcessor textProc{};
	textProc.SetOutputFormat(OutputFormat::markdown);

	textProc.AppendList({ "item 1", "item 2", "item 3" });
	cout << textProc.str() << endl;

	textProc.Clear();
	textProc.SetOutputFormat(OutputFormat::html);
	textProc.AppendList({ "item 1", "item 2", "item 3" });
	cout << textProc.str() << endl; 

	// setting up a static Strategy is easy: add template argument to the TextProcessor, 
	// which instantiates a private variable of type T, then use that object in AppendList()
	// obviously SetOutputFormat() can no longer exist. It's basically a less robust version
	// of the dynamic strategy, but it's there if you want it. 
}