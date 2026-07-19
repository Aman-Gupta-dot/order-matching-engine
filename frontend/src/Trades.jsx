function Trades({showTradeBook,tradeBookData,loadTrades}){
    
    return (
        <div className="mt-4 h-60 overflow-y-auto  scrollbar pr-2">
                 
                    { tradeBookData!=null &&
                                <div className="flex justify-between my-5">
                                    <span>Total Trades</span>
                                    <span>{tradeBookData.totalTrades}</span>
                                </div>
                                }
        { tradeBookData!=null && tradeBookData.Trades.map((trade)=>{//7question mark defending if tradeBook dsta null initially (basically acts as a guard)

                return(
                <div  key={trade.tradeId} >
                            
                            
                            <div>
                                <div className="flex justify-between">
                                    <span>Stock Name</span>
                                    <span>{trade.stockName}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Traded Id</span>
                                    <span>{trade.tradeId}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span>Buy OrderId</span>
                                    <span>{trade.buyOrderId}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span>Sell OrderId</span>
                                    <span>{trade.sellOrderId}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span>Traded Quantity</span>
                                    <span>{trade.tradingQuantity}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span>Trade Price</span>
                                    <span>{trade.tradePrice}</span>
                                </div>
                                <div className="flex justify-between">
                                    <span>Trade Time Stamp</span>
                                    <span>{trade.timeStamp}</span>
                                </div>
                            </div>
                            <div className="my-3">

                            </div>
                        </div>)
        })}
                
                
                
        </div>
    )
}

export default Trades;