<div class="h-screen w-screen flex flex-col p-8 pt-4 gap-4">

	<div>
		<slot name="header">
			Header here
		</slot>
	</div>

	<div class="grid grid-cols-3 gap-4 gap-4 grow">
		<div class="col-span-1 row-span-6 border border-primary p-4">
			<slot name="players">
				Player list here
			</slot>
		</div>

		<div class="col-span-2 row-span-4 border border-primary p-4">
			<slot name="draw">
				Canvas thing (Hoang will do this)
			</slot>
		</div>

		<div class="col-span-2 row-span-2 border border-primary p-4">
			<slot name="interact">
				Chatting here			
			</slot>
		</div>
	</div>
</div>

