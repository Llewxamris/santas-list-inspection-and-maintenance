# Santa's List Inspection and Maintenance (SLIM)
A bug tracking service reskinned to be Santa's digital naughty and nice list.
For 420-C30.

# Design
This is an application in support for Santa’s List Inspection and Maintenance
(SLIM). The system is to track the boys and girls on Santa’s naughty and nice
lists. This system will have a server component running PHP which is used by
the elves to create new and update existing list items. This will be done using
an all-in-one page.

Santa and Mrs. Claus want to be able to view the list information by selecting
the information from a list. They use a windows desktop browser or mobile phone
(responsive design required) to access the lists. Their “dashboard” displays
a list of the current good boys and girls and allows them to select one to
display details. Santa can NOT make changes to the list (he does not know how
to type).

Santa is accessing a node.js web server for all his web needs. His
“dashboard" must update automatically every 30 seconds to display the current
good girls and boys.

# Dependencies
Node.js server requires Chalk v.1.1.3, and Request 2.79.0. Newer versions may
cause issues with the server. Run `npm install` inside `node/` to install
dependencies automatically.

Web pages included rely on Bootstrap and jQuery. Both are brought in via CDN
with SRI to verify the resources have not been tampered with.

# License
Licensed under the GNU GENERAL PUBLIC LICENSE 3.0. Please see the LICENSE file
for more information.
