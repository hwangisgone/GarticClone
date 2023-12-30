<div class="h-screen w-screen flex flex-col p-4 gap-4">

    <div>
        <slot name="header">
            Header here
        </slot>
    </div>

    <div class="grid grid-cols-4 gap-4 gap-4 grow h-full ">
        <div class="col-span-1 row-span-6 border border-primary p-4 overflow-y-auto backgr">
            <slot name="players">
                Player list here
            </slot>
        </div>

        <div class="col-span-3 row-span-4 border border-primary p-4 overflow-y-auto backgr">
            <slot name="draw">
                Canvas thing (Hoang will do this)
            </slot>
        </div>

        <div class="col-span-2 row-span-2 border border-primary p-4 overflow-y-auto backgr">
            <slot name="interact">
                Chatting here
            </slot>
        </div>

        <div class="col-span-1 row-span-2 border border-primary p-4 overflow-y-auto backgr">
            <slot name="bottomright">
                anything here
            </slot>
        </div>
    </div>
</div>


<style>
	.backgr{
	    background-color: white;
	}
</style>
