<?php
/*
 * Retrieves a JSON object based on the parameter "which".
 */
$list = $_GET['which']; // Get the list type to search for

const FILE_NAME = './List/SantaList.json'; // Constant for the name of the file

$json_string = file_get_contents(FILE_NAME) 
    or die ('Error: Cannot get JSON file'); // Retrieve the file, or end

$json_file = json_decode($json_string, true); // Decode the JSON file

$return_json = '{ "person": ['; // Opening JSON tags, and "person" array key

foreach ($json_file['person'] as $value) {
    // For each key in the person array...
    if ($value['curList'] == $list) {
        // ...if the value for the key "crrList" is $list
        $return_json .= "{";
        foreach ($value as $input => $output) {
            // ...then for each key:value pair in the array, add the
            // key:value pair to $return_json
            $return_json .= "\"$input\": \"" . $output  . "\",";
        }
        $return_json .= "},";
    }
}

$return_json = rtrim($return_json, ","); // Remove the trailing comma
$return_json .= "]}"; // Closing JSON tags

// Set the response headers content type and length
header("Content-Type: application/json");
header("Content-Length: " . strlen($return_json));

echo $return_json;
