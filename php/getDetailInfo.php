<?php
/* Retrieves all the information from a specific person based on the
 * id parameter passed in by GET  
 */
$id = $_GET['id']; // Get the id of the person wanted

const FILE_NAME = './List/SantaList.json'; // Constant for the name of the file

$json_string = file_get_contents(FILE_NAME)
    or die ('Error: Cannot get JSON file'); // Retrieve the file, or end

$json_file = json_decode($json_string, true); // Decode the JSON file

$return_html = "";

foreach ($json_file['person'] as $value) {
    // For each key in the person array...
    if ($value['-id'] == $id) {
        // ...if the value for the key "-id" is $id...
        foreach ($value as $input => $output) {
            // ...then for each key:value pair in the array, echo out
            // the key:value as HTML.
           $return_html .= "<p>$input: $output</p>"; 
        }
    }
}

header("Content-Type: text/html");
header("Content-Length: " . strlen($return_html));
echo $return_html;
