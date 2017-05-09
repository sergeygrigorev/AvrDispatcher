function handler(){
	$(this).toggleClass('selected');
	var s = 0;
	$('td.selected').each(function(x) {s += parseInt($(this).attr('data'));});
	output.text(s);
}

$(function(){
	output = $('#output');
	$('td[data]').click(handler);
});
	
