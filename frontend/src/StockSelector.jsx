
function StockSelector({selectedStock,setSelectedStock}){
    return(
        <>
            

            <div className="flex items-center justify-center gap-3 m-1 ">
                                        
                                        <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                        {
                                            
                                            setSelectedStock("DairyMilk");
                                        }}>
                                        {selectedStock=="DairyMilk" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        
                                         Dairy Milk
                                    </button>
                                    
                                    <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setSelectedStock("5Star");
                                    }}>
                                    {selectedStock=="5Star" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        5 Star
                                    </button>
                                     <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setSelectedStock("FerreroRocher");
                                    }}>
                                    {selectedStock=="FerreroRocher" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        Ferrero Rocher
                                    </button>
                                     <button className="flex items-center justify-center gap-2 border border-slate-800 px-5 py-0.5 rounded-xl hover:bg-slate-700" type="button" onClick={()=>
                                    {
                                        
                                        setSelectedStock("KinderJoy");
                                    }}>
                                    {selectedStock=="KinderJoy" && (<div className="w-2 h-2 rounded-full bg-white"></div>)}
                                        Kinder Joy
                                    </button>
                            </div>
        </>
    )
}

export default StockSelector;