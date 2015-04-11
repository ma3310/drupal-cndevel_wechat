<?php
/**
 * @file
 * Administration page callbacks for the cnDevel WeChat module.
 * only be loaded before options / settings are configured.
 */

/**
 * Form builder. Configure cnDevel WeChat module.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function cndevel_wechat_admin_settings() {
// Get an array of node types with internal names as keys and
// "friendly names" as values. E.g.,
// array('page' => ’Basic Page, 'article' => 'Articles')

//    [article] => stdClass Object (
//        [type] => article
//        [name] => Article
//        [base] => node_content
//        [description] => Use articles for time-sensitive content like news, press releases
//            or blog posts.
//            [help] =>
//        [has_title] => 1
//        [title_label] => Title
//        [has_body] => 1
//        [body_label] => Body
//        [custom] => 1
//        [modified] => 1
//        [locked] => 0
//        [orig_type] => article
//    )

    $types = node_type_get_types();

    foreach($types as $node_type) {
        $options[$node_type->type] = $node_type->name;
    }
    $form['cndevel_wechat_node_types'] = array(
        '#title' => t('Users may annotate these content types'),
        '#description' => t('A text field will be available on these content types to make user-specific notes.'),
        '#type' => 'checkboxes',
        '#options' => $options,
        '#default_value' => variable_get('cndevel_wechat_node_types', array('page')),
    );


    $form['#submit'][] = 'cndevel_wechat_admin_settings_submit';

    return system_settings_form($form);
}

/**
 * Process annotation settings submission.
 */
function cndevel_wechat_admin_settings_submit($form, $form_state) {
// Loop through each of the content type checkboxes shown on the form.
    foreach ($form_state['values']['annotate_node_types'] as $key => $value) {
// If the check box for a content type is unchecked, look to see whether
// this content type has the annotation field attached to it using the
// field_info_instance function. If it does then we need to remove the
// annotation field as the administrator has unchecked the box.
        if (!$value) {
            $instance = field_info_instance('node', 'annotation', $key);
            if (!empty($instance)) {
                field_delete_instance($instance);
                watchdog("Annotation", 'Deleted annotation field from content type:
%key', array('%key' => $key));
            }
        } else {
// If the check box for a content type is checked, look to see whether
// the field is associated with that content type. If not then add the
// annotation field to the content type.
            $instance = field_info_instance('node', 'annotation', $key);
            if (empty($instance)) {
                $instance = array(
                    'field_name' => 'annotation',
                    'entity_type' => 'node',
                    'bundle' => $key,
                    'label' => t('Annotation'),
                    'widget_type' => 'text_textarea_with_summary',
                    'settings' => array('display_summary' => TRUE),
                    'display' => array(
                        'default' => array(
                            'type' => 'text_default',
                        ),
                        'teaser' => array(
                            'type' => 'text_summary_or_trimmed',
                        ),
                    ),
                );
                $instance = field_create_instance($instance);
                watchdog('Annotation', 'Added annotation field to content type: %key',
                    array('%key' => $key));
            }
        }
    } // End foreach loop.
}

/**
 * Form builder.
 * Configure Enterprise Account related options.
 *
 * @ingroup forms
 * @see system_settings_form().
 * @link http://qydev.weixin.qq.com/debug
 */
function cndevel_wechat_enterprise_admin_settings() {

    watchdog("cnDevel WeChat Module", "cndevel_wechat_enterprise_admin_settings()");

    $form['WeChatEnterpriseCorpID'] = array(
        '#title' => t('CorpID'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseCorpID', ''), // 取不到变量时使用空字符串
                                                                        // checkboxes 值会是 array
    );
    $form['WeChatEnterpriseSecret'] = array(
        '#title' => t('Secret'),
        '#description' => t('Get this information from privilege management sub-page of settings page.<br>
Application has to be put in non-SystemAdmin group first, then use Secret of that group.'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseSecret', ''),
    );
    $form['WeChatEnterpriseAppID'] = array(
        '#title' => t('AppID'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseAppID', ''),
    );
    $form['WeChatEnterpriseToken'] = array(
        '#title' => t('Token'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseToken', ''),
    );
    $form['WeChatEnterpriseEncodingAESKey'] = array(
        '#title' => t('EncodingAESKey'),
        '#type' => 'textfield',
        '#default_value' => variable_get('WeChatEnterpriseEncodingAESKey', ''),
    );

    $form['#submit'][] = 'cndevel_wechat_enterprise_admin_settings_submit';

    return system_settings_form($form);
}


function cndevel_wechat_enterprise_admin_settings_submit ($form, $form_state){
    if ( !empty($form_state['values']['WeChatEnterpriseCorpID']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseSecret']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseAppID']) ){
        watchdog("cnDevel WeChat Module", "WeChatEnterpriseAppID: %value", array('%value'=>$form_state['values']['WeChatEnterpriseAppID']));
        
    }
    if ( !empty($form_state['values']['WeChatEnterpriseToken']) ){

    }
    if ( !empty($form_state['values']['WeChatEnterpriseEncodingAESKey']) ){

    }
}

