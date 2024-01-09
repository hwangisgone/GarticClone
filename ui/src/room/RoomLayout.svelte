<div class="container mx-auto">

<div class="h-[5vh] text-3xl">
	<slot name="header">
		Header here
	</slot>
</div>

<div class="grid grid-cols-4">
  <div class="h-[95vh] p-4 pr-0 col-span-1 flex flex-col">
	<div class="flex-1 overflow-y-auto border-4 border-primary rounded-xl">
		<slot name="players">
			Player list here
		</slot>
	</div>
<!-- 	<div class="h-1/4">
	  <p>Fixed-size content at the bottom</p>
	</div> -->
  </div>
  <div class="h-[95vh] p-4 col-span-3 flex flex-col">
	<div class="h-3/4 border-4 border-primary">
		<slot name="draw">
			Canvas
		</slot>
	</div>
	<div class="h-1/4 border-4 border-primary">
		<slot name="interact">
			Chatting here			
		</slot>
	</div>
  </div>
</div>

</div>

