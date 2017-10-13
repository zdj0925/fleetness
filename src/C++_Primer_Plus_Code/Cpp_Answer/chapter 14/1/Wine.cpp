#include "Wine.h"


namespace n_wine
{
	using std::cin;
	using std::cout;
	using std::endl;
	using std::cerr;

	// ====================================
	// 公有成员函数
	// ====================================

	Wine::Wine (const string& name, unsigned years_total, unsigned vintage_years[], unsigned bottles_total[])
		:	name_(name),
			years_total_(years_total), 
			vintage_year_and_bottles_total_(UnsignedArray(vintage_years, years_total), UnsignedArray(bottles_total, years_total))
	{
		;
	}
	
	Wine::Wine (const string& name, unsigned years_total)
		:	name_(name),
			years_total_(years_total), 
			vintage_year_and_bottles_total_(UnsignedArray(years_total), UnsignedArray(years_total))
	{
		;
	}

	const string&
	Wine::getLabel (void) const
	{
		return (name_);
	}

	void
	Wine::getBottles (void)
	{
		cout << "Enter "<< name_ << " data for " << years_total_ << " year(s) ---- \n";

		for (unsigned i = 0; i < years_total_; ++i) {
			unsigned	vintage_year;
			cout << "Enter year: ";
			cin >> vintage_year;
			if (!cin) {
				cerr << "ERREOR! " << __FILE__ << ", " << __LINE__ << endl;
				exit(EXIT_FAILURE);
			}
			vintage_year_and_bottles_total_.first[i] = vintage_year;

			unsigned	bottles_total;
			cout << "Enter bottles for that year: ";
			cin >> bottles_total;
			if (!cin) {
				cerr << "ERREOR! " << __FILE__ << ", " << __LINE__ << endl;
				exit(EXIT_FAILURE);
			}
			vintage_year_and_bottles_total_.second[i] = bottles_total;
		}
	}

	void
	Wine::show (void) const
	{
		cout << "Wine: " << name_ << '\n';

		cout << '\t' << "Year" << '\t' << "Bottles" << '\n';
		for (unsigned i = 0; i < years_total_; ++i) {
			cout << '\t' << vintage_year_and_bottles_total_.first[i] << '\t' << vintage_year_and_bottles_total_.second[i] << endl;
		}
	}

	unsigned
	Wine::sum (void) const
	{
		return (vintage_year_and_bottles_total_.second.sum());
	}
}
