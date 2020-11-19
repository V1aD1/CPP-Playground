#include <string>
#include <iostream>

using namespace std;

struct IEuroPricedGood {
	virtual float GetPriceInEuros() const = 0;
};

struct GermanGood : IEuroPricedGood {
	GermanGood(float price) : m_priceInEuros(price) {}

	virtual float GetPriceInEuros() const override
	{
		return m_priceInEuros;
	}

private:
	float m_priceInEuros;
};

struct IAmericanPricedGood {
	virtual float GetPriceInDollars() const = 0;
};

struct AmericanGood:IAmericanPricedGood {
	AmericanGood(float price) : m_priceInDollars(price) {}

	virtual float GetPriceInDollars() const override
	{
		return m_priceInDollars;
	}

private:
	float m_priceInDollars;
};

struct AmericanCostProcessor {
	// this object expects to deal only with American goods, in American prices
	static float CalculateTotalCost(const IAmericanPricedGood& good) {
		return (1.0f + m_taxRate / 100.0f) * good.GetPriceInDollars();
	}
private:
	static const float m_taxRate;
};

const float AmericanCostProcessor::m_taxRate = 10;

struct GermanToAmericanPricedGoodAdapter: IAmericanPricedGood{
	float m_priceInDollars;

	GermanToAmericanPricedGoodAdapter(GermanGood good)
	{
		float costAfterExport = (1.0f + m_GermanyToAmericaExportTax) * good.GetPriceInEuros();
		m_priceInDollars = costAfterExport * m_euroToDollarExchangeRate;
	}

	virtual float GetPriceInDollars() const override
	{
		return m_priceInDollars;
	}

private:
	static const float m_euroToDollarExchangeRate;
	static const float m_GermanyToAmericaExportTax;
};

const float GermanToAmericanPricedGoodAdapter::m_euroToDollarExchangeRate = 1.1f;
const float GermanToAmericanPricedGoodAdapter::m_GermanyToAmericaExportTax = 0.1f;

void AdapterExample() {
	// ok, so we want to sell some German good in America
	GermanGood gg{ 100 };

	// but AmericanCostProcessor expects an IAmericanPricedGood, 
	// so we will convert the GermanGood to an IAmericanPricedGood with an adapter
	GermanToAmericanPricedGoodAdapter adaptedGood{ gg };
	float totalCost = AmericanCostProcessor::CalculateTotalCost(adaptedGood);

	cout << "The total cost of the German good, if it were to be sold in USA, is: " << totalCost << " USD" << endl;
}