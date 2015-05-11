<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $rows: An array of row items. Each row is an array of content
 * - $totals: An array of calculated totals. Each row contains the total for one calculation.
 *   keyed by field ID.
 * @ingroup views_templates
 */
if (empty($rows) && empty($totals)) {
  return;
} 

foreach ($totals as $type => $row): ?>
      <tr class="view-footer-number">
        <?php foreach ($row as $field => $content): ?>
          <td class="view-footer views-field views-field-<?php print $fields[$field]; ?>  <?php print $options['info'][$field]['align'] ?>">
            <?php
				if ($fields[$field] == 'field-adnan-spent') {
					$adnan_spent = $content;
				} else if ($fields[$field] == 'field-natesh-spent') {
                        $natesh_spent = $content;
                } else if ($fields[$field] == 'field-sathish-spent') {
                        $sathish_spent = $content;
                } else if ($fields[$field] == 'field-adnan-exp') {
                        $adnan_exp = $content;
                } else if ($fields[$field] == 'field-natesh-exp') {
                        $natesh_exp = $content;
                } else if ($fields[$field] == 'field-sathish-exp') {
                        $sathish_exp = $content;
                }?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; 
     $adnan_net = number_format($adnan_spent - $adnan_exp, 2, '.', '');
	   $natesh_net = number_format($natesh_spent - $natesh_exp, 2, '.', '');
     $sathish_net = number_format($sathish_spent - $sathish_exp, 2, '.', '');
     $adnan_net_class = ($adnan_net < 0) ? "negative" : "postive";
     $natesh_net_class = ($natesh_net < 0) ? "negative" : "postive";
     $sathish_net_class = ($sathish_net < 0) ? "negative" : "postive";
    $h_net = array();
     if ($adnan_net > 0) {
      $h_net = array();
      $h_net['name'] = 'Adnan';
      $h_net['amt'] = $adnan_net;
      $high_net[] = $h_net;
     } else {
      $l_net = array();
      $l_net['name'] = 'Adnan';
      $l_net['amt'] = $adnan_net;
      $least_net[] = $l_net;
     }
     if ($natesh_net > 0) {
      $h_net = array();
      $h_net['name'] = 'Natesh';
      $h_net['amt'] = $natesh_net;
      $high_net[] = $h_net;
     } else {
      $l_net = array();
      $l_net['name'] = 'Natesh';
      $l_net['amt'] = $natesh_net;
      $least_net[] = $l_net;
     }
     if ($sathish_net > 0) {
      $h_net = array();
      $h_net['name'] = 'Sathish';
      $h_net['amt'] = $sathish_net;
      $high_net[] = $h_net;
     } else {
      $l_net = array();
      $l_net['name'] = 'Sathish';
      $l_net['amt'] = $sathish_net;
      $least_net[] = $l_net;
     }
    $owe_table = '<table class="amount-owe"><thead><tr><th>Name</th><th>Amount Owe</th></tr></thead><tbody>';
    if (count($high_net) == 2) {
       $owe_table .= '<tr class="even"><td>' . $least_net[0]['name'] . ' owe ' . $high_net[0]['name'] .'</td><td><span class="amt">' . number_format($high_net[0]['amt'], 2, '.', '') . '</span></td></tr>';
       $owe_table .= '<tr class="odd1"><td>' . $least_net[0]['name'] . ' owe ' . $high_net[1]['name'] .'</td><td><span class="amt">' . number_format($high_net[0]['amt'], 2, '.', '') . '</span></td></tr>';
    } else {
      $owe_table .= '<tr class="even"><td>' . $least_net[0]['name'] . ' owe ' . $high_net[0]['name'] .'</td><td><span class="amt">'. number_format(abs($least_net[0]['amt']), 2, '.', '') . '</span></td></tr>';
      $owe_table .= '<tr class="odd1"><td>' . $least_net[1]['name'] . ' owe ' . $high_net[0]['name'] .'</td><td><span class="amt">' . number_format(abs($least_net[1]['amt']), 2, '.', '') . '</span></td></tr>';
    }
 $owe_table .='</tbody></table>';
     ?>
     <div class="view-header">
      <p></p><h3>Car Pool Summary</h3>
    </div>
<table class="car-pool-summary">
<thead>
    <tr class="odd1"><th>Name</th><th>Total Spent</th><th>Total Expense</th><th>Net Amount</th></tr>
</thead>
 <tbody>
 <tr class="even"><td>Adnan</td><td><?php print $adnan_spent; ?></td><td><?php print $adnan_exp; ?></td><td class="<?php print $adnan_net_class; ?>"><?php print $adnan_net; ?></td></tr>
 <tr class="odd1"><td>Natesh</td><td><?php print $natesh_spent; ?></td><td><?php print $natesh_exp; ?></td><td class="<?php print $natesh_net_class; ?>"><?php print $natesh_net; ?></td></tr>
 <tr class="even"><td>Sathish</td><td><?php print $sathish_spent; ?></td><td><?php print $sathish_exp; ?></td><td class="<?php print $sathish_net_class; ?>"><?php print $sathish_net; ?></td></tr>
 </tbody>
 </table>
 <?php print $owe_table ?>
<div class="view-header">
      <p></p><h3>Car Pool Data</h3>
    </div>
<table class="<?php print $class; ?>">
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>
  <thead>
    <tr>
      <?php foreach ($header as $field => $label): ?>
        <th class="views-field views-field-<?php print $fields[$field]; ?> <?php print $options['info'][$field]['align'] ?>">
          <?php print $label; ?>
        </th>
      <?php endforeach; ?>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($rows as $count => $row): ?>
      <tr class="<?php print ($count % 2 == 0) ? 'even' : 'odd1';?>">
        <?php foreach ($row as $field => $content): ?>
          <td class="views-field views-field-<?php print $fields[$field]; ?>  <?php print $options['info'][$field]['align'] ?>">
            <?php print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
  <tfoot>
    <?php foreach ($sub_totals as $type => $row): ?>
      <tr class="view-subfooter-number">
        <?php foreach ($row as $field => $content): ?>
          <td class="view-subfooter views-field views-field-<?php print $fields[$field]; ?>  <?php print $options['info'][$field]['align'] ?>">
            <?php print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
    <?php foreach ($totals as $type => $row): ?>
      <tr class="view-footer-number">
        <?php foreach ($row as $field => $content): ?>
          <td class="view-footer views-field views-field-<?php print $fields[$field]; ?>  <?php print $options['info'][$field]['align'] ?>">
            <?php
				if ($fields[$field] == 'field-adnan-spent') {
					$adnan_spent = $content;
				} else if ($fields[$field] == 'field-natesh-spent') {
                        $natesh_spent = $content;
                } else if ($fields[$field] == 'field-sathish-spent') {
                        $sathish_spent = $content;
                } else if ($fields[$field] == 'field-adnan-exp') {
                        $adnan_exp = $content;
                } else if ($fields[$field] == 'field-natesh-exp') {
                        $natesh_exp = $content;
                } else if ($fields[$field] == 'field-sathish-exp') {
                        $sathish_exp = $content;
                }
                if($fields[$field] == 'field-car-pool-date') {
                	continue;
                }
                if($fields[$field] == 'body') {
                	print "Total SUM";
                	continue;
                }
		 print $content; ?>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tfoot>
</table>
