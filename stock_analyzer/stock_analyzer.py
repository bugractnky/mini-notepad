import yfinance as yf
import matplotlib.pyplot as plt

def fetch_stock_data(ticker, period="3mo"):
    data = yf.download(ticker, period=period)
    return data

def plot_stock(data, ticker):
    plt.figure(figsize=(10, 5))
    plt.plot(data['Close'], label='Kapanış Fiyatı')
    plt.plot(data['Close'].rolling(window=5).mean(), label='5 Günlük Ort.', linestyle='--')
    plt.title(f"{ticker} - Fiyat Grafiği")
    plt.xlabel("Tarih")
    plt.ylabel("Fiyat")
    plt.legend()
    plt.grid()
    plt.tight_layout()
    plt.savefig(f"{ticker}_grafik.png")
    plt.show()

def main():
    ticker = input("Hisse senedi kodunu girin (örnek: AAPL, THYAO.IS): ").upper()
    period = input("Veri periyodu (1mo, 3mo, 6mo, 1y vs): ") or "3mo"
    data = fetch_stock_data(ticker, period)
    
    if data.empty:
        print("Veri çekilemedi. Kod doğru mu?")
        return
    
    print(data.tail())
    plot_stock(data, ticker)

if __name__ == "__main__":
    main()
