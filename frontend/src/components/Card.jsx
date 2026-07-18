function Card({children})
{
    return(
        <>
            <div className="bg-slate-850 border border-slate-600 rounded-xl p-6 shadow-md text-white flex flex-col transition-all hover:bg-slate-850 overflow-hidden ">
                <div>
                    {children}
                </div>
            </div>
        </>
    )
}

export default Card;