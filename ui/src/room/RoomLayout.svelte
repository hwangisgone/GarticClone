<div class="h-screen w-screen flex flex-col p-8 pt-4 gap-4">

	<div>
		<slot name="header">
			Header here
		</slot>
	</div>

	<div class="grid grid-cols-4 gap-4 bg-white h-full">
		<div class="col-span-1 border border-primary p-4 h-full">
			<slot name="players">
				Player list here
			</slot>
		</div>

		<div class="col-span-3 gap-4 p-4">
			<slot name="draw">
				Canvas thing (Hoang will do this)
			</slot>
			<slot name="interact">
				Chatting here			
			</slot>
		</div>
	</div>
</div>

