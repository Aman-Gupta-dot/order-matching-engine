import React from "react";

function Statistics({ loadStatistics, showStatistics, statsResponseData }) {
    return (
        <>
            <div>
                <div>
                    <button 
                        className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" 
                        type="button" 
                        onClick={() => {
                            loadStatistics();
                        }}
                    >
                        View Statistics
                    </button>
                </div>
                
                {
                    statsResponseData != null && (
                        <div className="space-y-5">
                            <h2 className="text-xl font-bold">
                                Market Statistics
                            </h2>
                            
                            <div>
                                <h3 className="text-lg font-bold border-b border-slate-700 pb-1 mb-2">
                                    Trading
                                </h3>

                                <div className="flex justify-between">
                                    <span>Total Trades</span>
                                    <span>{statsResponseData.totalTrades}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Traded Quantity</span>
                                    <span>{statsResponseData.totalTradedQuantity}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Traded Value</span>
                                    <span>{statsResponseData.totalTradedValue}</span>
                                </div>
                            </div>

                            <div>
                                <h3 className="text-lg font-semibold border-b border-slate-700 pb-1 mb-2">
                                    Orders
                                </h3>

                                <div className="flex justify-between">
                                    <span>Orders Received</span>
                                    <span>{statsResponseData.ordersReceived}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Orders Cancelled</span>
                                    <span>{statsResponseData.ordersCancelled}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Active Buy Orders</span>
                                    <span>{statsResponseData.activeBuyOrders}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Active Sell Orders</span>
                                    <span>{statsResponseData.activeSellOrders}</span>
                                </div>
                            </div>

                            <div>
                                <h3 className="text-lg font-semibold border-b border-slate-700 pb-1 mb-2">
                                    Market
                                </h3>

                                <div className="flex justify-between">
                                    <span>Best Bid</span>
                                    <span className="text-green-400">{statsResponseData.bestBid}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Best Ask</span>
                                    <span className="text-red-400">{statsResponseData.bestAsk}</span>
                                </div>
                            </div>

                            <div>
                                <h3 className="text-lg font-semibold border-b border-slate-700 pb-1 mb-2">
                                    Volume
                                </h3>

                                <div className="flex justify-between">
                                    <span>Buy Volume</span>
                                    <span>{statsResponseData.buyVolume}</span>
                                </div>

                                <div className="flex justify-between">
                                    <span>Sell Volume</span>
                                    <span>{statsResponseData.sellVolume}</span>
                                </div>
                            </div>
                        </div>
                    )
                }
            </div>        
        </>
    );
}

export default Statistics;
