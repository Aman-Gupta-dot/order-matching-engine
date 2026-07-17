function Trades({showTradeBook,tradeBookData,loadTrades}){
    
    return (
        <>
        <div>
            <button onClick={()=>{
                loadTrades();
            }}
            >View Trades</button>

        </div> 
        <div className="TradeBookContainer">
            {
                showTradeBook&& 
                    <pre>
                        {JSON.stringify(tradeBookData,null,2)}
                    </pre>
            }
        </div>
        </>
    )
}

export default Trades;