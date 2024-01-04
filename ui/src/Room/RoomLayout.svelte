<div class="h-screen w-screen flex flex-col p-8 pt-4 gap-4">

	<div>
		<slot name="header">
			Header here
		</slot>
	</div>

	<div class="grid grid-cols-4 gap-4 gap-4 grow" style="background-color:white">
		<div class="col-span-1 row-span-6 border border-primary p-4">
			<slot name="players">
				Player list here
			</slot>
		</div>

		<div class="col-span-3 row-span-5 border border-primary p-4">
			<slot name="draw">
				Canvas thing (Hoang will do this)
			</slot>
		</div>

		<div class="col-span-3 row-span-1 border border-primary p-4">
			<slot name="interact">
				Chatting here			
			</slot>
		</div>
	</div>
</div>

