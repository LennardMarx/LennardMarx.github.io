function getDate() {
  // Get the current date
  var now = new Date();

  // Extract day, month, and year
  var day = now.getDate();
  var month = now.toLocaleString('default', { month: 'short' }); // Get the 3-letter month abbreviation
  var year = now.getFullYear().toString().substr(-2); // Get the last two digits of the year

  // Pad single digit day with leading zero
  day = day < 10 ? '0' + day : day;

  // Output the date in dd-mm-yy format
  var currentDate = day + '-' + month + '-' + year;

  // Print or use currentDate as needed
  document.write(currentDate);
}
